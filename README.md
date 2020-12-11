# BasicSPH

**BasicSPH** is a basic implementation of Smoothed Particle Hydrodynamics (SPH).

## SPH

See [SPH introduction](documents/SPH_intro.pdf)as reference.<sup>[1](#sph_intro_footnote)</sup>

[SPH](https://en.wikipedia.org/wiki/Smoothed-particle_hydrodynamics) is a computational method for solving partial differential equations ([PDEs](https://en.wikipedia.org/wiki/Partial_differential_equation)). It's a meshfree Lagrangian method, which makes it ideal to simulate problems dominated by complex boundary dynamics. 

![Basic idea](documents/pictures/basic_idea.png?raw=true "Basic idea of SPH")

### Advantages

* suitable for parallelization
* many application fields
* great conservation features
* ... 

### Implementation

#### Flow diagram of a SPH simulation

![Flow diagram of a SPH simulation](documents/pictures/flow_diagram.png?raw=true "Flow diagram")


---
<a name="sph_intro_footnote">1</a>: Smoothed Particle Hydrodynamics, written by Oliver Wandel, Roland Speith and Christoph Schäfer.
