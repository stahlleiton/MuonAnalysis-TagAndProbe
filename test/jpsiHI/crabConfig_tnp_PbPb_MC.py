from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.section_('General')
config.General.requestName = 'TnP_HISingleMuon_PbPb5TeV_2018_JPsi_MC_20190120'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'tnp_PbPb_MC.py'
config.JobType.maxMemoryMB = 2400

config.section_('Data')
config.Data.inputDataset = '/JpsiMM_5p02TeV_TuneCP5/anstahll-JpsiMM_5p02TeV_TuneCP5_Embd_RECO_20190117-5db5dfa073297cb96791f14c622e83e2/USER'
config.Data.inputDBS = 'phys03'
config.Data.unitsPerJob = 1
config.Data.splitting = 'FileBased'
config.Data.outLFNDirBase = '/store/user/%s/TagAndProbe/PbPb2018/TnP/%s' % (getUsernameFromSiteDB(), config.General.requestName)
config.Data.publication = False
config.Data.outputDatasetTag = config.General.requestName

config.section_('Site')
config.Data.ignoreLocality = True
config.Site.whitelist = ['T1_FR_*','T2_FR_*','T2_CH_*','T2_US_*','T3_FR_*']
config.Site.storageSite = 'T2_FR_GRIF_LLR'
