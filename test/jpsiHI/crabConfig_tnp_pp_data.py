from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.section_('General')
config.General.requestName = 'TNP_SingleMuLowPt_Run2015E_PromptReco_v1_AOD_20160813'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'tnp_pp_data.py'
config.JobType.maxMemoryMB = 2500
config.JobType.outputFiles = ['tnpJPsi_Data_pp5TeV_AOD.root']

config.section_('Data')
config.Data.inputDataset = '/SingleMuLowPt/Run2015E-PromptReco-v1/AOD'
config.Data.inputDBS = 'global'
config.Data.unitsPerJob = 10
config.Data.splitting = 'LumiBased'
config.Data.runRange = '262081-262328'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/5TeV/Cert_262081-262328_5TeV_PromptReco_Collisions15_25ns_JSON_MuonPhys.txt'
config.Data.outLFNDirBase = '/store/group/phys_heavyions/%s/TagAndProbe2015/%s' % (getUsernameFromSiteDB(), config.General.requestName)
config.Data.publication = False

config.section_('Site')
config.Site.storageSite = 'T2_CH_CERN'
