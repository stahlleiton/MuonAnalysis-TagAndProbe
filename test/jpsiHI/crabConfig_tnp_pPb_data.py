from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.section_('General')
config.General.requestName = 'TNP_HIOniaTnP_HIRun2016_PromptReco_v1_AOD_20180813'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'tnp_pPb_data.py'
config.JobType.maxMemoryMB = 2500
config.JobType.outputFiles = ['tnpJPsi_Data_Pbp_AOD.root']

config.section_('Data')
config.Data.inputDataset = '/PASingleMuon/PARun2016C-PromptReco-v1/AOD'
config.Data.inputDBS = 'global'
config.Data.unitsPerJob = 5
config.Data.splitting = 'LumiBased'
#Pbp (1st run)
config.Data.runRange = '285479-285832'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/HI/Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
#pPb (2nd run)
#config.Data.runRange = '285952-286496'
#config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/HI/Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
config.Data.outLFNDirBase = '/store/group/phys_heavyions/dileptons/%s/TagAndProbe2016/%s' % (getUsernameFromSiteDB(), config.General.requestName)
config.Data.publication = False

config.section_('Site')
config.Site.storageSite = 'T2_CH_CERN'
