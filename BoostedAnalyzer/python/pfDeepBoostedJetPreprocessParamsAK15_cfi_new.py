import FWCore.ParameterSet.Config as cms

pfDeepBoostedJetPreprocessParams = cms.PSet(
    input_names = cms.vstring(
        'pfcand', 
        'sv'
    ),
    pfcand = cms.PSet(
        input_shape = cms.vuint32(1, 42, 100, 1),
        var_infos = cms.PSet(
            pfcand_VTX_ass = cms.PSet(
                median = cms.double(7.0),
                norm_factor = cms.double(1.0)
            ),
            pfcand_abseta = cms.PSet(
                median = cms.double(0.721823811531),
                norm_factor = cms.double(1.47439721157)
            ),
            pfcand_btagEtaRel = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(0.4314179074)
            ),
            pfcand_btagJetDistVal = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(1.0)
            ),
            pfcand_btagPParRatio = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(1.01851448142)
            ),
            pfcand_btagPtRatio = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(2.81067194023)
            ),
            pfcand_btagSip2dSig = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(2.4453850533)
            ),
            pfcand_btagSip2dVal = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(638.007597176)
            ),
            pfcand_btagSip3dSig = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(1.15971550287)
            ),
            pfcand_btagSip3dVal = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(250.83996437)
            ),
            pfcand_charge = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(1.0)
            ),
            pfcand_deltaR = cms.PSet(
                median = cms.double(0.457400307059),
                norm_factor = cms.double(1.64462890187)
            ),
            pfcand_detadeta = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(1384189.05251)
            ),
            pfcand_dlambdadz = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(1.0)
            ),
            pfcand_dphidphi = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(633881.290064)
            ),
            pfcand_dphidxy = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(1.0)
            ),
            pfcand_dptdpt = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(81430.6663369)
            ),
            pfcand_drminsv = cms.PSet(
                median = cms.double(0.289193272591),
                norm_factor = cms.double(1.30484650259)
            ),
            pfcand_drsubjet1 = cms.PSet(
                median = cms.double(0.458710297942),
                norm_factor = cms.double(1.41576461919)
            ),
            pfcand_drsubjet2 = cms.PSet(
                median = cms.double(0.615583866835),
                norm_factor = cms.double(1.47819974207)
            ),
            pfcand_dxy = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(185.004521812)
            ),
            pfcand_dxydxy = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(28643.3553062)
            ),
            pfcand_dxydz = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(9047247.43836)
            ),
            pfcand_dxysig = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(2.70883772011)
            ),
            pfcand_dz = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(120.117307428)
            ),
            pfcand_dzdz = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(23758.7010115)
            ),
            pfcand_dzsig = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(2.04741266848)
            ),
            pfcand_erel_log = cms.PSet(
                median = cms.double(-5.43041038513),
                norm_factor = cms.double(0.619938826494)
            ),
            pfcand_etarel = cms.PSet(
                median = cms.double(-0.0470333751291),
                norm_factor = cms.double(2.81393632141)
            ),
            pfcand_hcalFrac = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(1.0)
            ),
            pfcand_isChargedHad = cms.PSet(
                median = cms.double(1.0),
                norm_factor = cms.double(1.0)
            ),
            pfcand_isEl = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(1.0)
            ),
            pfcand_isGamma = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(1.0)
            ),
            pfcand_isMu = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(1.0)
            ),
            pfcand_isNeutralHad = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(1.0)
            ),
            pfcand_lostInnerHits = cms.PSet(
                median = cms.double(-1.0),
                norm_factor = cms.double(1.0)
            ),
            pfcand_normchi2 = cms.PSet(
                median = cms.double(999.0),
                norm_factor = cms.double(1.0)
            ),
            pfcand_phirel = cms.PSet(
                median = cms.double(-5.66476464883e-05),
                norm_factor = cms.double(2.26875301689)
            ),
            pfcand_pt_log = cms.PSet(
                median = cms.double(0.523826658726),
                norm_factor = cms.double(0.597586482673)
            ),
            pfcand_ptrel_log = cms.PSet(
                median = cms.double(-5.3821451664),
                norm_factor = cms.double(0.615251197629)
            ),
            pfcand_puppiw = cms.PSet(
                median = cms.double(1.0),
                norm_factor = cms.double(1.0)
            ),
            pfcand_quality = cms.PSet(
                median = cms.double(0.0),
                norm_factor = cms.double(0.2)
            )
        ),
        var_length = cms.uint32(100),
        var_names = cms.vstring(
            'pfcand_pt_log', 
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
            'pfcand_btagJetDistVal'
        )
    ),
    sv = cms.PSet(
        input_shape = cms.vuint32(1, 15, 7, 1),
        var_infos = cms.PSet(
            sv_abseta = cms.PSet(
                median = cms.double(0.715122997761),
                norm_factor = cms.double(1.41904912364)
            ),
            sv_costhetasvpv = cms.PSet(
                median = cms.double(0.999684274197),
                norm_factor = cms.double(3311.07479771)
            ),
            sv_d3d = cms.PSet(
                median = cms.double(0.461652815342),
                norm_factor = cms.double(0.401915968381)
            ),
            sv_d3dsig = cms.PSet(
                median = cms.double(7.01869082451),
                norm_factor = cms.double(0.034680699204)
            ),
            sv_deltaR = cms.PSet(
                median = cms.double(0.293338418007),
                norm_factor = cms.double(2.29772297257)
            ),
            sv_dxy = cms.PSet(
                median = cms.double(0.315444037318),
                norm_factor = cms.double(0.570401442023)
            ),
            sv_dxysig = cms.PSet(
                median = cms.double(7.00221896172),
                norm_factor = cms.double(0.0346856044257)
            ),
            sv_erel_log = cms.PSet(
                median = cms.double(-2.72214770317),
                norm_factor = cms.double(1.00734994172)
            ),
            sv_etarel = cms.PSet(
                median = cms.double(-0.0274098170921),
                norm_factor = cms.double(4.36200815155)
            ),
            sv_mass = cms.PSet(
                median = cms.double(1.28788304329),
                norm_factor = cms.double(0.562450928238)
            ),
            sv_normchi2 = cms.PSet(
                median = cms.double(0.781157135963),
                norm_factor = cms.double(0.774733456056)
            ),
            sv_ntracks = cms.PSet(
                median = cms.double(3.0),
                norm_factor = cms.double(0.5)
            ),
            sv_phirel = cms.PSet(
                median = cms.double(0.000541293120477),
                norm_factor = cms.double(3.44686675751)
            ),
            sv_pt_log = cms.PSet(
                median = cms.double(3.26421976089),
                norm_factor = cms.double(0.939772790254)
            ),
            sv_ptrel_log = cms.PSet(
                median = cms.double(-2.65555870533),
                norm_factor = cms.double(1.00796003857)
            )
        ),
        var_length = cms.uint32(7),
        var_names = cms.vstring(
            'sv_pt_log', 
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
            'sv_costhetasvpv'
        )
    )
)

