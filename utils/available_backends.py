import matplotlib
#gui_env = ['TKAgg', 'GTKAgg', 'Qt4Agg', 'WXAgg', 'MacOSX', 'Gtk3Agg', 'Qt5Agg']
gui_env = ['pdf', 'pgf', 'Qt4Agg', 'GTK', 'GTKAgg', 'ps', 'agg', 'cairo', 'MacOSX', 'GTKCairo', 'WXAgg', 'template',
           'TkAgg', 'GTK3Cairo', 'GTK3Agg', 'svg', 'WebAgg', 'CocoaAgg', 'emf', 'gdk', 'WX', 'Qt5Agg']
working = []

for gui in gui_env:

    try:
        print("testing: " + str(gui))
        matplotlib.use(gui,warn=False, force=True)
        from matplotlib import pyplot as plt
        working.append(gui)
    except:
        continue

print(" ")
for gui in working:
    print("Working: ", gui)

print(" ")
print("Using:",matplotlib.get_backend())
