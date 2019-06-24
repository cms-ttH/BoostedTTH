import FWCore.ParameterSet.Config as cms

pfDeepBoostedJetPreprocessParams = cms.PSet(
    input_names = cms.vstring('pfcand', 
        'sv'),
    pfcand = cms.PSet(
        input_shape = cms.vuint32(1, 42, 100, 1),
        var_infos = cms.PSet(
            pfcand_VTX_ass = cms.PSet(
                median = cms.double(7.0),
                upper = cms.double(7.0)
            ),
            pfcand_abseta = cms.PSet(
                median = cms.double(0.721823811531),
                upper = cms.double(1.40006709099)
            ),
            pfcand_btagEtaRel = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(2.31793808937)
            ),
            pfcand_btagJetDistVal = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.0)
            ),
            pfcand_btagPParRatio = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.98182207346)
            ),
            pfcand_btagPtRatio = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.355786808729)
            ),
            pfcand_btagSip2dSig = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.408933553696)
            ),
            pfcand_btagSip2dVal = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.00156737945508)
            ),
            pfcand_btagSip3dSig = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.862280445099)
            ),
            pfcand_btagSip3dVal = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.00398660557345)
            ),
            pfcand_charge = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(1.0)
            ),
            pfcand_deltaR = cms.PSet(
                median = cms.double(0.457400307059),
                upper = cms.double(1.0654402113)
            ),
            pfcand_detadeta = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(7.22444667645e-07)
            ),
            pfcand_dlambdadz = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.0)
            ),
            pfcand_dphidphi = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(1.57758245223e-06)
            ),
            pfcand_dphidxy = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.0)
            ),
            pfcand_dptdpt = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(1.22803858176e-05)
            ),
            pfcand_drminsv = cms.PSet(
                median = cms.double(0.289193272591),
                upper = cms.double(1.05556694031)
            ),
            pfcand_drsubjet1 = cms.PSet(
                median = cms.double(0.458710297942),
                upper = cms.double(1.16504240036)
            ),
            pfcand_drsubjet2 = cms.PSet(
                median = cms.double(0.615583866835),
                upper = cms.double(1.29208242893)
            ),
            pfcand_dxy = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.00540527328849)
            ),
            pfcand_dxydxy = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(3.49121110048e-05)
            ),
            pfcand_dxydz = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(1.10530855579e-07)
            ),
            pfcand_dxysig = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.369162018299)
            ),
            pfcand_dz = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.00832519493997)
            ),
            pfcand_dzdz = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(4.20898431912e-05)
            ),
            pfcand_dzsig = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.488421320915)
            ),
            pfcand_erel_log = cms.PSet(
                median = cms.double(-5.43041038513),
                upper = cms.double(-3.81734800339)
            ),
            pfcand_etarel = cms.PSet(
                median = cms.double(-0.0470333751291),
                upper = cms.double(0.308340693712)
            ),
            pfcand_hcalFrac = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.0)
            ),
            pfcand_isChargedHad = cms.PSet(
                median = cms.double(1.0),
                upper = cms.double(1.0)
            ),
            pfcand_isEl = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.0)
            ),
            pfcand_isGamma = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(1.0)
            ),
            pfcand_isMu = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.0)
            ),
            pfcand_isNeutralHad = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.0)
            ),
            pfcand_lostInnerHits = cms.PSet(
                median = cms.double(-1.0),
                upper = cms.double(-1.0)
            ),
            pfcand_normchi2 = cms.PSet(
                median = cms.double(999.0),
                upper = cms.double(999.0)
            ),
            pfcand_phirel = cms.PSet(
                median = cms.double(-5.66476464883e-05),
                upper = cms.double(0.440714116096)
            ),
            pfcand_pt_log = cms.PSet(
                median = cms.double(0.523826658726),
                upper = cms.double(2.197224617)
            ),
            pfcand_ptrel_log = cms.PSet(
                median = cms.double(-5.3821451664),
                upper = cms.double(-3.75679278374)
            ),
            pfcand_puppiw = cms.PSet(
                median = cms.double(1.0),
                upper = cms.double(1.0)
            ),
            pfcand_quality = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(5.0)
            )
        ),
        var_length = cms.uint32(100),
        var_names = cms.vstring('pfcand_pt_log', 
            'pfcand_ptrel_log', 
            'pfcand_erel_log', 
            'pfcand_phirel', 
            'pfcand_etarel', 
            'pfcand_deltaR', 
            'pfcand_abseta', 
            'pfcand_puppiw', 
            'pfcand_drminsv', 
            'pfcand_drsubjet1', 
            'pfcand_drsubjet2', 
            'pfcand_charge', 
            'pfcand_isMu', 
            'pfcand_isEl', 
            'pfcand_isChargedHad', 
            'pfcand_isGamma', 
            'pfcand_isNeutralHad', 
            'pfcand_hcalFrac', 
            'pfcand_VTX_ass', 
            'pfcand_lostInnerHits', 
            'pfcand_normchi2', 
            'pfcand_quality', 
            'pfcand_dz', 
            'pfcand_dzsig', 
            'pfcand_dxy', 
            'pfcand_dxysig', 
            'pfcand_dptdpt', 
            'pfcand_detadeta', 
            'pfcand_dphidphi', 
            'pfcand_dxydxy', 
            'pfcand_dzdz', 
            'pfcand_dxydz', 
            'pfcand_dphidxy', 
            'pfcand_dlambdadz', 
            'pfcand_btagEtaRel', 
            'pfcand_btagPtRatio', 
            'pfcand_btagPParRatio', 
            'pfcand_btagSip2dVal', 
            'pfcand_btagSip2dSig', 
            'pfcand_btagSip3dVal', 
            'pfcand_btagSip3dSig', 
            'pfcand_btagJetDistVal')
    ),
    sv = cms.PSet(
        input_shape = cms.vuint32(1, 15, 7, 1),
        var_infos = cms.PSet(
            sv_abseta = cms.PSet(
                median = cms.double(0.715122997761),
                upper = cms.double(1.41982023716)
            ),
            sv_costhetasvpv = cms.PSet(
                median = cms.double(0.999684274197),
                upper = cms.double(0.999986290932)
            ),
            sv_d3d = cms.PSet(
                median = cms.double(0.461652815342),
                upper = cms.double(2.94973509789)
            ),
            sv_d3dsig = cms.PSet(
                median = cms.double(7.01869082451),
                upper = cms.double(35.8531729126)
            ),
            sv_deltaR = cms.PSet(
                median = cms.double(0.293338418007),
                upper = cms.double(0.728551893234)
            ),
            sv_dxy = cms.PSet(
                median = cms.double(0.315444037318),
                upper = cms.double(2.06859528542)
            ),
            sv_dxysig = cms.PSet(
                median = cms.double(7.00221896172),
                upper = cms.double(35.832623291)
            ),
            sv_erel_log = cms.PSet(
                median = cms.double(-2.72214770317),
                upper = cms.double(-1.72944401741)
            ),
            sv_etarel = cms.PSet(
                median = cms.double(-0.0274098170921),
                upper = cms.double(0.201842390895)
            ),
            sv_mass = cms.PSet(
                median = cms.double(1.28788304329),
                upper = cms.double(3.0658159256)
            ),
            sv_normchi2 = cms.PSet(
                median = cms.double(0.781157135963),
                upper = cms.double(2.07192364693)
            ),
            sv_ntracks = cms.PSet(
                median = cms.double(3.0),
                upper = cms.double(5.0)
            ),
            sv_phirel = cms.PSet(
                median = cms.double(0.000541293120477),
                upper = cms.double(0.29065984726)
            ),
            sv_pt_log = cms.PSet(
                median = cms.double(3.26421976089),
                upper = cms.double(4.32830675125)
            ),
            sv_ptrel_log = cms.PSet(
                median = cms.double(-2.65555870533),
                upper = cms.double(-1.66345588207)
            )
        ),
        var_length = cms.uint32(7),
        var_names = cms.vstring('sv_pt_log', 
            'sv_ptrel_log', 
            'sv_erel_log', 
            'sv_phirel', 
            'sv_etarel', 
            'sv_deltaR', 
            'sv_abseta', 
            'sv_mass', 
            'sv_ntracks', 
            'sv_normchi2', 
            'sv_dxy', 
            'sv_dxysig', 
            'sv_d3d', 
            'sv_d3dsig', 
            'sv_costhetasvpv')
    )
)