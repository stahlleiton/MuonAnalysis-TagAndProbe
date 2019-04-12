from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.section_('General')
config.General.requestName = 'TNP_SingleMu_pp5TeVRun2017G_PromptReco_v1_AOD_20190327'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = './jpsiHI/tnp_pp_data.py'
#config.JobType.maxMemoryMB = 2500
#config.JobType.outputFiles = ['tnpJPsi_Data_pp5TeVRun2017G_AOD.root']

config.section_('Data')
config.Data.inputDataset = '/SingleMuon/Run2017G-17Nov2017-v1/AOD'
config.Data.inputDBS = 'global'
config.Data.unitsPerJob = 25
config.Data.splitting = 'LumiBased'
config.Data.runRange = '306546-306657'
config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions17/5TeV/PromptReco/Cert_306546-306657_5TeV_PromptReco_Collisions17_JSON_MuonPhys.txt'
config.Data.outLFNDirBase = '/store/user/%s/TagAndProbe2017/%s' % (getUsernameFromSiteDB(), config.General.requestName)#'/store/group/phys_heavyions/%s/TagAndProbe2017/%s' % (getUsernameFromSiteDB(), config.General.requestName)
config.Data.publication = False

config.section_('Site')
#config.Site.blacklist = ['T1_US_FNAL']
config.Site.storageSite = 'T2_FR_GRIF_LLR'#config.Site.storageSite = 'T2_CH_CERN'
