import os
import sys

from optparse import OptionParser
import ROOT
ROOT.gROOT.SetBatch(True)
ROOT.PyConfig.IgnoreCommandLineOptions = True


def parse_arguments():
	parser = OptionParser()
	parser.add_option("-s", "--sample",
						help = "path to .root file containing the histograms to merge and the luminosity for these runs",
						metavar = "path/to/rootfile,LUMINOSITY",
						dest = "samples",
						type = "str",
						action = "append"
				)
	parser.add_option("-o", "--outfile",
						help = "path to .root file to save output in (default: merged_output.root)",
						dest = "outfile",
						type = "str",
						default = "merged_output.root"
				)
	parser.add_option("-a", "--switch-axes",
						help = "switch the axes of the input TH2 histograms, i.e. make x->y and vice versa (default: False)",
						dest = "switch_axes",
						action = "store_true",
						default = False
				)
	options, args = parser.parse_args()
	return options

def print_all_bins(h1, h2):
	nbinsX = h1.GetNbinsX()
	nbinsY = h1.GetNbinsY()

	for x in range(1, nbinsX+1):
		for y in range(1, nbinsY+1):
			print "\tbin {0},{1}:\t{2}/{3}\t({4}/{5})".format(x,y,h1.GetBinContent(x,y),h2.GetBinContent(x,y),h1.GetBinError(x,y),h2.GetBinError(x,y))

def merge_histograms(sample_lumi_pairs):
	merged_histos = {}
	lumi_ges = 0
	for nsample, pair in enumerate(sample_lumi_pairs):
		filepath, lumistring = pair.split(",")
		if not os.path.exists(filepath):
			sys.exit("File '%s' does not exist! Abort" % filepath)
		lumi = None
		try:
			lumi = float(lumistring)
		except Exception as e:
			print "ERROR: Could not convert lumi from input pair:", pair
			raise e
		print "opening file", filepath
		f = ROOT.TFile.Open(filepath)
		if not (f.IsOpen() and not f.IsZombie() and not f.TestBit(ROOT.TFile.kRecovered)):
			sys.exit("File '%s' is corrupted, aborting..." % filepath)
		keynames = [x.GetName() for x in f.GetListOfKeys()]
		if not nsample == 0:
			keys = merged_histos.keys()
			if not all(k in keynames for k in keys):
				sys.exit("ERROR: Not all keys from previous input file are present in file %s" % filepath)
		for k in keynames:
			print "\tanalyzing key", k, "\t(lumi:%s)" % str(lumi)
			h = f.Get(k)
			if not isinstance(h, ROOT.TH1):
				continue
			if nsample == 0:
				merged_histos[k] = h.Clone()
				merged_histos[k].SetDirectory(0)
				merged_histos[k].Reset()
			else:
				if not k in merged_histos:
					sys.exit("ERROR: keyname '%s' did not exist in previous input file!" % k)
			h.Scale(lumi)
			# h.Print("range")
			merged_histos[k].Add(h)
			# merged_histos[k].Print("range")
			# print_all_bins(h, merged_histos[k])
		lumi_ges += lumi
		f.Close()
	print "Overall lumi collected:", lumi_ges
	for histname in merged_histos:
		merged_histos[histname].Scale(1./lumi_ges)
		# merged_histos[histname].Print("range")
	return merged_histos

def get_ranges(axis):
	minval = axis.GetBinLowEdge(axis.GetFirst())
	maxval = axis.GetBinUpEdge(axis.GetLast())
	return minval, maxval

def check_val(val1, val2):
	if not val1 == val2:
		print "val1 =", orig_min
		print "val2 =", new_min
		sys.exit("ERROR: mismatch in values!")

def sanity_checks(h_orig, h_new):
	print "checking histogram", h_new.GetName()
	#check axis ranges
	orig_min, orig_max = get_ranges(h_orig.GetYaxis())
	new_min, new_max = get_ranges(h_new.GetXaxis())
	print "\tchecking x min"
	check_val(val1 = orig_min, val2 = new_min)
	print "\tchecking x max"
	check_val(val1 = orig_max, val2 = new_max)

	orig_min, orig_max = get_ranges(h_orig.GetXaxis())
	new_min, new_max = get_ranges(h_new.GetYaxis())
	print "\tchecking y min"
	check_val(val1 = orig_min, val2 = new_min)
	print "\tchecking y max"
	check_val(val1 = orig_max, val2 = new_max)


def invert_axes(input_histo_dict):
	out_histo_dict = {}
	for hname in input_histo_dict:
		h_orig = input_histo_dict[hname]
		h_orig.SetName(hname+"_orig")
		
		nbinsX = h_orig.GetNbinsX()
		xaxis = h_orig.GetXaxis()
		xmin, xmax = get_ranges(h_orig.GetXaxis())

		nbinsY = h_orig.GetNbinsY()
		ymin, ymax = get_ranges(h_orig.GetYaxis())

		h = ROOT.TH2D(hname, "", nbinsY, ymin, ymax, nbinsX, xmin, xmax)
		h.SetDirectory(0)
		h.GetXaxis().SetTitle(h_orig.GetYaxis().GetTitle())
		h.GetYaxis().SetTitle(h_orig.GetXaxis().GetTitle())
		h.SetTitle(h_orig.GetTitle())

		for x in range(1, nbinsX+1):
			for y in range(1, nbinsY+1):
				val = h_orig.GetBinContent(x, y)
				error = h_orig.GetBinError(x, y)
				h.SetBinContent(y,x,val)
				h.SetBinError(y,x,error)
		sanity_checks(h_orig = h_orig, h_new = h)
		out_histo_dict[hname] = h
	return out_histo_dict


def save_histos(histo_dict, outfilepath):
	if len(histo_dict) > 0:
		outfile = ROOT.TFile.Open(outfilepath, "RECREATE")
		for n in histo_dict:
			outfile.WriteTObject(histo_dict[n])
		outfile.Close()
	else:
		print "Did not receive any histograms to write, will not create '%s'" % outfilepath


def main(options):
	sample_lumi_pairs = options.samples
	outfile = options.outfile
	switch_axes = options.switch_axes

	merged_histos = merge_histograms(sample_lumi_pairs)

	if switch_axes:
		merged_histos = invert_axes(merged_histos)
	save_histos(histo_dict = merged_histos, outfilepath = outfile)



if __name__ == '__main__':
	options = parse_arguments()

	main(options = options)