
from pylab import *

fig = figure( figsize=[5,5], frameon=False )


#  The larger, background grid
#
ax = axes([0.025,0.025,0.95,0.95], alpha=0.0)

color1 = 'green'

for side in (['bottom', 'top', 'left', 'right']):
    ax.spines[side].set_color(color1)
    ax.spines[side].set_linestyle('dashed')
    ax.spines[side].set_linewidth(3.5)

ax.set_xlim(0,5)
ax.set_ylim(0,5)
ax.xaxis.set_major_locator(MultipleLocator(1.0))
ax.yaxis.set_major_locator(MultipleLocator(1.0))
ax.grid(which='major', axis='x', linewidth=3.50, linestyle='dashed', color=color1)
ax.grid(which='major', axis='y', linewidth=3.50, linestyle='dashed', color=color1)
ax.set_xticklabels([])
ax.set_yticklabels([])
#ax.tick_params( bottom='off', top='off', left='off', right='off' )

# draw a dot
plot(.5,.5, marker='o', markerfacecolor=color1, markersize=8)


# The smaller, foreground grid
#

ax2 = axes( [0.025, 0.025, .760, .760], alpha=0.0, frameon=True)
#print dir(ax2)

ax2.set_axis_bgcolor([1.,1.,1.,0.])

color2 = 'orange'

for side in (['bottom', 'top', 'left', 'right']):
    ax2.spines[side].set_color(color2)
    ax2.spines[side].set_linewidth(2.5)
    ax2.spines[side].set_alpha(1.0)

ax2.set_xlim(0,4)
ax2.set_ylim(0,4)
ax2.set_alpha(0.0)
ax2.xaxis.set_major_locator(MultipleLocator(2.0))
ax2.yaxis.set_major_locator(MultipleLocator(2.0))
ax2.grid(which='major', axis='x', linewidth=2.50, linestyle='-', color=color2, alpha=1.0)
ax2.grid(which='major', axis='y', linewidth=2.50, linestyle='-', color=color2, alpha=1.0)
ax2.set_xticklabels([])
ax2.set_yticklabels([])
#ax2.tick_params( bottom='off', top='off', left='off', right='off' )

# draw a dot
plot(1.,1., marker='o', markerfacecolor=color2, markersize=10)

#show()
savefig('pixelgrid.eps')
