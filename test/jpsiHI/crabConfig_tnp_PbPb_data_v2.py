from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.section_('General')
config.General.requestName = 'TnP_HISingleMuon_v2_PbPb5TeV_2018_JPsi_Data_20190115'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'tnp_PbPb_data.py'
config.JobType.maxMemoryMB = 2400

config.section_('Data')
config.Data.inputDataset = '/HISingleMuon/HIRun2018A-PromptReco-v2/AOD'
config.Data.inputDBS = 'global'
config.Data.unitsPerJob = 60
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/HI/DCSOnly/json_DCSONLY_HI.txt'
config.Data.runRange = '326381-327564'
config.Data.outLFNDirBase = '/store/user/%s/TagAndProbe/PbPb2018/TnP/%s' % (getUsernameFromSiteDB(), config.General.requestName)
config.Data.publication = False
config.Data.outputDatasetTag = config.General.requestName

config.section_('Site')
config.Site.storageSite = 'T2_FR_GRIF_LLR'
