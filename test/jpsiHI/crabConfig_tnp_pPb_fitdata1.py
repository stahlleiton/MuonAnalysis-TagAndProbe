from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.workArea = 'crab_projects_pPb_fitdata1'
## --- Auxiliary code starts here --- ##
## We want to define config.General.requestName = 'tasknumber<index>'
import os
index =1 
base_request_name = 'scenario'
config.General.requestName = base_request_name + str(index)
config.General.transferOutputs = True
config.General.transferLogs = False

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'tp_Ana_MuId_RD_pPb_Scenario1.py'
config.JobType.maxMemoryMB = 2500
config.JobType.outputFiles = ["tnp_Ana_RD_MuId_pPb_%s.root" % index]
#config.JobType.inputFiles = ["/afs/cern.ch/user/o/okukral/Work/public/TnP_pPb/tnpJPsi_Data_pPb-mergedPartial.root"]

config.section_('Data')
config.Data.outputPrimaryDataset = 'tnpJPsi_Data_pPb-mergedPartial'
#config.Data.outputPrimaryDataset = '/afs/cern.ch/user/o/okukral/Work/public/TnP_pPb/tnpJPsi_Data_pPb-mergedPartial.root'
config.Data.userInputFiles = ['/afs/cern.ch/user/o/okukral/Work/public/TnP_pPb/tnpJPsi_Data_pPb-mergedPartial.root']
#config.Data.inputDBS = 'global'
config.Data.unitsPerJob = 10
config.Data.splitting = 'FileBased'
#pPb (2nd run)
#config.Data.runRange = '285952-286496'
#config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/HI/Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
config.Data.outLFNDirBase = '/store/group/phys_heavyions/dileptons/%s/TagAndProbe2016/Fits/%s' % (getUsernameFromSiteDB(), config.General.requestName)
config.Data.publication = False
    
config.section_('Site')
config.Site.storageSite = 'T2_CH_CERN'


