# Visualizing particle tracks in a magnetic field.
[morphologica](https://github.com/ABRG-Models/morphologica) must be installed in-tree with the code.

## Mathematics
I'm Using the Lorentz equation for my simulation:
$$\mathbf{F} = q(\mathbf{E} + \mathbf{v} \times \mathbf{B})$$

Which can be stated explicitly as:
$$\mathnormal{\overline{\boldsymbol{F}}\left(\overline{r}( t) ,\dot{\overline{r}}( t) ,t,q\right)} =q\left[\overline{\boldsymbol{E}}(\overline{r} ,t) +\dot{\overline{r}}( t) \times \overline{\boldsymbol{B}}(\overline{r} ,t)\right]$$


## Current state
At the moment, the code shows the electric potential around a number of point charges, with positions $${x,y,z}$$ and magnitude $$q$$. See pointcharge() in [calculation.h](calculation.h). The electric potential is defined to be
$$\overline(V)=k\frac{q}{\overline(r)}$$

Points (as well as the size of the grid) can be defined in a json file, with [params.json](params.json) and [onepoint.json](onepoint.json) as example files.
