// Copyright  (C)  2007  Ruben Smits <ruben dot smits at mech dot kuleuven dot be>

#ifndef KDL_CHAIN_IKSOLVERVEL_PINV_BOOST_GIVENS_HPP
#define KDL_CHAIN_IKSOLVERVEL_PINV_BOOST_GIVENS_HPP

#include "chainiksolver.hpp"
#include "chainjnttojacsolver.hpp"

#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

namespace ublas = boost::numeric::ublas;

namespace KDL
{
    /**
     * Implementation of a inverse velocity kinematics algorithm based
     * on the generalize pseudo inverse to calculate the velocity
     * transformation from Cartesian to joint space of a general
     * KDL::Chain. It uses a svd-calculation based on householders
     * rotations.
     *
     * @ingroup KinematicFamily
     */
    class ChainIkSolverVel_pinv_boost_givens : public ChainIkSolverVel
    {
    public:
        /** 
         * Constructor of the solver
         * 
         * @param chain the chain to calculate the inverse velocity
         * kinematics for
         * @param eps if a singular value is below this value, its
         * inverse is set to zero, default: 0.00001
         * @param maxiter maximum iterations for the svd calculation,
         * default: 150
         * 
         */
        ChainIkSolverVel_pinv_boost_givens(const Chain& chain);
        ~ChainIkSolverVel_pinv_boost_givens();
        
        virtual int CartToJnt(const JntArray& q_in, const Twist& v_in, JntArray& qdot_out);
        /** 
         * not (yet) implemented.
         * 
         */
        virtual int CartToJnt(const JntArray& q_init, const FrameVel& v_in, JntArrayVel& q_out){return -1;};
    private:        
        const Chain chain;
        ChainJntToJacSolver jnt2jac;
        Jacobian jac;
        bool transpose,toggle;
        int m,n;
        ublas::matrix<double> jac_boost;
        ublas::matrix<double> U;
        ublas::matrix<double> V;
        ublas::vector<double> S;
        ublas::matrix<double> B;
        ublas::vector<double> tempi;
        ublas::vector<double> tempj;
        ublas::vector<double> UY;
        ublas::vector<double> SUY;
        ublas::vector<double> qdot_boost;
        ublas::vector<double> v_in_boost;
                
    };
}
#endif
