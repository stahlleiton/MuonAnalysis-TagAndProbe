from CRABClient.UserUtilities import config, getUsernameFromCRIC
config = config()

config.section_('General')
config.General.requestName = 'TnP_HINPbPbAutumn18DR-mva98_JPsi_MC_20201024'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'tnp_PbPb_MC.py'
config.JobType.maxMemoryMB = 2300
config.JobType.maxJobRuntimeMin = 940
config.JobType.allowUndistributedCMSSW = True

config.section_('Data')
config.Data.inputDataset = '/JPsi_pThat-2_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM'
config.Data.inputDBS = 'global'
config.Data.unitsPerJob = 4
config.Data.splitting = 'FileBased'
config.Data.outLFNDirBase = '/store/group/phys_heavyions/%s/TagAndProbe/PbPb2018/TnP/%s' % (getUsernameFromCRIC(), config.General.requestName)
config.Data.publication = False
config.Data.allowNonValidInputDataset = True
config.Data.outputDatasetTag = config.General.requestName

config.section_('Site')
config.Data.ignoreLocality = True
config.Site.whitelist = ['T1_FR_*','T1_US_*','T2_FR_*','T2_US_*','T2_CH_CERN']
config.Site.storageSite = 'T2_CH_CERN'
