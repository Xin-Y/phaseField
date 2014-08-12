//Parameters list for beta prime precipitation evolution problem

//define problem dimensions
#define problemDIM 1
#define spanX 100.0
#define spanY 100.0
#define spanZ 100.0

//define mesh parameters
#define refineFactor 7
#define finiteElementDegree 2

//define time step parameters
#define dt 5.0e-3
#define numIncrements 10000

//define results output parameters
#define writeOutput true
#define skipOutputSteps 10

//define general physics parameters
#define numStructuralOrderParameters 1

//define Cahn-Hilliard parameters (No Gradient energy)
#define Mc 1.0

//define Allen-Cahn parameters
#define MnVals {0.1}
#define KnVals {4.0}

//define free energy expressions
#define faV (-1.6704-4.776*c+5.1622*c*c-2.7375*c*c*c+1.3687*c*c*c*c)
#define facV (-4.776 + 10.3244*c - 8.2125*c*c + 5.4748*c*c*c)
#define faccV (10.3244-16.425*c+16.4244*c*c)
#define fbV (5.0*c*c-5.9746*c-1.5925)
#define fbcV (10.0*c-5.9746)
#define fbccV (10.0)
#define hV (10.0*n[0]*n[0]*n[0]-15.0*n[0]*n[0]*n[0]*n[0]+6.0*n[0]*n[0]*n[0]*n[0]*n[0])
#define hnV (30.0*n[0]*n[0]-60.0*n[0]*n[0]*n[0]+30.0*n[0]*n[0]*n[0]*n[0])

//define required residuals
#define rcV (c)
#define rcxV (mux)
#define rmuV ( (1.0-hV)*facV+hV*fbcV ) 
#define rnV  (n[0]+(-Mn[0]*dt)*(fbV-faV)*hnV )
#define rnxV (nx[0])
