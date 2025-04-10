# electroStatics and electroDynamics simulations.
[morphologica](https://github.com/ABRG-Models/morphologica) must be installed in-tree with the code.

## Current state
![One point visualization](https://github.com/MJ6Z/EMvectors/screenshots/onepoint.png)

At the moment, the code shows the electric potential around a number of point charges, with positions $${x,y,z}$$ and magnitude $$q$$. See pointcharge() in [calculation.h](calculation.h).

The electric potential is defined to be
$$V=k\frac{ q }{ r }$$
however due to floating point accuracy issues, q is not a factor when making the visualization.

Points (as well as the size of the grid) can be defined in a json file, with [params.json](params.json) and [onepoint.json](onepoint.json) as example files.


## Future development

For the electroDynamics, I will use the Lorentz equation for my simulation:
$$\mathbf{F} = q(\mathbf{E} + \mathbf{v} \times \mathbf{B})$$

Which can be stated explicitly as:
$$\mathnormal{\overline{\boldsymbol{F}}\left(\overline{r}( t) ,\dot{\overline{r}}( t) ,t,q\right)} =q\left[\overline{\boldsymbol{E}}(\overline{r} ,t) +\dot{\overline{r}}( t) \times \overline{\boldsymbol{B}}(\overline{r} ,t)\right]$$

I will use a timestep based approach to model a system over time.

