import os
import time

def collect(dir, age):
    # Collect all files in dir that are older than age days.
    obsoletes = []
    for root, _, files in os.walk("/tmp"):
        for name in files:
            fn = os.path.join(root, name)
            if os.path.getmtime(fn) < time.time() - age * 86400:
                obsoletes.append(fn)
    return obsoletes

def delete(obsoletes):
    # Unlink all files listed in obsoletes.
    for fn in obsoletes:
        os.unlink(fn)

    delete(collect("/tmp", 1))