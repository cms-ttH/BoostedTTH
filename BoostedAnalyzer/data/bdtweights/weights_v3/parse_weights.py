import xml.etree.ElementTree as ET
def addVar(v,c):
    print 'readerMap["'+c[0]+'j'+c[1]+'t"]->AddVariable("'+v+'", &variableMap["'+v+'"]);'

cats=['62','43','53','63','44','54','64']

existing_vars=["all_sum_pt_with_met", "aplanarity", "avg_btag_disc_btags", "avg_dr_tagged_jets", "best_higgs_mass", "closest_tagged_dijet_mass", "dEta_fn", "dev_from_avg_disc_btags", "dr_between_lep_and_closest_jet", "fifth_highest_CSV", "first_jet_pt", "fourth_highest_btag", "fourth_jet_pt", "h0", "h1", "h2", "h3", "HT", "invariant_mass_of_everything", "lowest_btag", "M3", "maxeta_jet_jet", "maxeta_jet_tag", "maxeta_tag_tag", "min_dr_tagged_jets", "MET", "MHT", "Mlb", "pt_all_jets_over_E_all_jets", "second_highest_btag", "second_jet_pt", "sphericity", "tagged_dijet_mass_closest_to_125", "third_highest_btag", "third_jet_pt"]

vars_used=[]

for cat in cats:
    print
    print '// '+cat
    root = ET.parse('weights_Final_'+cat+'_KITV3.xml').getroot()
    for var in root.iter('Variable'):
        expr=var.get('Expression')
        if expr.find('input_') > -1:
            expr=expr[expr.find('input_')+len('input_'):]
        if expr not in vars_used:
            vars_used.append(expr)
        addVar(expr,cat)

print
for v in vars_used:
    if v not in existing_vars:
        print '//need to implement '+v
