from multiprocessing.dummy import Pool as PoolThread
from os import listdir, system
from fnmatch import filter


def run_preselection_parallel(i):
    system("cp /data/3/retrieved/2017.12.06_0001/" + i +
           ".hld.bz2" + " /data/1/users/nikodem/data_run5/")
    system("bxip2 -d /data/1/users/nikodem/data_run5/" + i + ".hld.bz2")
    system("./Run4Preselection -t hld -f " + i +
           ".hld -p conf_trb3.xml -u userParams.json -i 5 -l detectorSetupRun5.json")
    system("rm /data/1/users/nikodem/data_run5/" + i + ".hld")
    system("rm /data/1/users/nikodem/data_run5/" + i + ".hld.root")
    system("rm /data/1/users/nikodem/data_run5/" + i + ".tslot.calib.root")
    system("rm /data/1/users/nikodem/data_run5/" + i + ".raw.sig.root")
    system("rm /data/1/users/nikodem/data_run5/" + i + ".phys.sig.root")
    system("rm /data/1/users/nikodem/data_run5/" + i + ".hits.root")


list_of_files = listdir("/data/3/retrieved/2017.12.06_0001/")

filenames = [file.split(".")[0] for file in list_of_files]


pool = PoolThread(25)

results = pool.map(run_analysis_parallel, list_of_files)
