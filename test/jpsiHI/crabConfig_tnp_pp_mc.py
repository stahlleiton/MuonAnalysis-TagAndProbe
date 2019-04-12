from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.section_('General')
config.General.requestName     = 'TNP_JpsiMM_5p02TeV_TuneCUETP8M1_RunIIpp5Spring18DR-94X_AODSIM_20190327'
config.General.workArea        = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs    = False

config.section_('JobType')
config.JobType.pluginName  = 'Analysis'
config.JobType.psetName    = './jpsiHI/tnp_pp_mc.py'
#config.JobType.outputFiles = ['tnpJPsi_MC_pp5TeV_AOD.root']

config.section_('Data')
config.Data.inputDataset  = '/JPsiMM_TuneCUETP8M1_5p02TeV_pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV-v2/AODSIM'
config.Data.inputDBS      = 'global'
config.Data.splitting     = 'FileBased'
config.Data.unitsPerJob   = 2

config.Data.outLFNDirBase = '/store/user/%s/TagAndProbe2017/%s' % (getUsernameFromSiteDB(), config.General.requestName)#'/store/group/phys_heavyions/%s/TagAndProbe2015/%s' % (getUsernameFromSiteDB(), config.General.requestName)
config.Data.publication   = False

config.section_('Site')
#config.Site.whitelist   = ["T2_US_MIT"]
config.Site.storageSite = 'T2_FR_GRIF_LLR'
