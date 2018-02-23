from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.section_('General')
config.General.requestName     = 'TNP_Pythia8_JpsiMM_ptJpsi_03_06_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-v1'
config.General.workArea        = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs    = False

config.section_('JobType')
config.JobType.pluginName  = 'Analysis'
config.JobType.psetName    = 'tnp_PbPb_mc.py'
config.JobType.maxMemoryMB = 2500
config.JobType.outputFiles = ['tnpJPsi_MC_PbPb_AOD.root']

config.section_('Data')
config.Data.inputDataset  = '/Pythia8_JpsiMM_ptJpsi_03_06_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-v1/AODSIM'
config.Data.inputDBS      = 'global'
config.Data.unitsPerJob   = 1
config.Data.splitting     = 'FileBased'
config.Data.outLFNDirBase = '/store/group/phys_heavyions/%s/TagAndProbe2015/%s' % (getUsernameFromSiteDB(), config.General.requestName)
config.Data.publication   = False

config.section_('Site')
config.Site.storageSite = 'T2_CH_CERN'
