//Parameter list for the Cahn-Hilliard spinodal decomposition problem

//define problem dimensions
#define problemDIM 2
#define spanX 100.0
#define spanY 100.0
#define spanZ 100.0

#define subdivisionsX 1
#define subdivisionsY 1
#define subdivisionsZ 1

//define mesh parameters
#define subdivisionsX 1
#define subdivisionsY 1
#define subdivisionsZ 1
#define refineFactor 6
#define finiteElementDegree 2

//adaptive refinement parameters
#define hAdaptivity true
#define maxRefinementLevel (refineFactor)
#define minRefinementLevel (0)
#define refinementDOF 1 //refining using composition field
#define topRefineFraction 0.99
#define bottomCoarsenFraction 0.01

//define number of fields in the problem
//c, mu
#define numFields 2

//define time step parameters
#define timeStep 5.0e-4
#define timeFinal 1000
#define timeIncrements 1000000

//define results output parameters
#define writeOutput true
#define skipOutputSteps 10000





