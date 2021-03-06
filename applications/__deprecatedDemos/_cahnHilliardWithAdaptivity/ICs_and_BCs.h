//initial condition function for concentration
//template <int dim>
//class InitialConditionC : public Function<dim>
//{
//public:
//  InitialConditionC () : Function<dim>(1) {
//    //seeding the random number generator
//    std::srand(Utilities::MPI::this_mpi_process(MPI_COMM_WORLD)+1);
//  }
//  double value (const Point<dim> &p, const unsigned int component = 0) const
//  {
//    //return the value of the initial concentration field at point p
//    return  0.5 + 0.2*(0.5 - (double)(std::rand() % 100 )/100.0);
//  }
//};

//initial condition function for concentration
template <int dim>
class InitialConditionC : public Function<dim>
{
public:
  InitialConditionC () : Function<dim>(1) {
    std::srand(Utilities::MPI::this_mpi_process(MPI_COMM_WORLD)+1);
  }
  double value (const Point<dim> &p, const unsigned int component = 0) const
  {
    //return the value of the initial concentration field at point p
    double dx=spanX/((double) subdivisionsX)/std::pow(2.0,refineFactor);
    double r=0.0;
#if problemDIM==1
    r=p[0];
    return 0.005+0.5*(0.125-0.005)*(1-std::tanh((r-spanX/2.0)/(3*dx)));
#elif problemDIM==2
    r=p.distance(Point<dim>(spanX/2.0,spanY/2.0));
    r=std::sqrt( (p[0]-spanX/2.0)*(p[0]-spanX/2.0) + (p[1]-spanY/2.0)*(p[1]-spanY/2.0)/1.5 );
    return 0.1+0.5*(1-std::tanh((r-spanX/8.0)/(3*dx)));
#elif problemDIM==3
    r=p.distance(Point<dim>(spanX/2.0,spanY/2.0,spanZ/2.0));
    return 0.005+0.5*(0.125-0.005)*(1-std::tanh((r-spanX/8.0)/(3*dx)));
#endif
  }
};


//apply initial conditions
template <int dim>
void CahnHilliardProblem<dim>::applyInitialConditions()
{
  unsigned int fieldIndex;
  //call initial condition function for c
  fieldIndex=this->getFieldIndex("c");
  VectorTools::interpolate (*this->dofHandlersSet[fieldIndex],	\
			    InitialConditionC<dim>(),			\
			    *this->solutionSet[fieldIndex]);
  //set initial condition for mu
  fieldIndex=this->getFieldIndex("mu");
  *(this->residualSet[fieldIndex])=0.0;
  this->matrixFreeObject.cell_loop (&CahnHilliardProblem<dim>::getRHS, this, this->residualSet, this->solutionSet);
  //sove for mu from initial condition for c
  for (unsigned int dof=0; dof<this->solutionSet[fieldIndex]->local_size(); ++dof){
    this->solutionSet[fieldIndex]->local_element(dof)= this->invM.local_element(dof)*this->residualSet[fieldIndex]->local_element(dof);
  }
}
