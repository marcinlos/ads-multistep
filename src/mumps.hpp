#ifndef MUMPS_HPP_
#define MUMPS_HPP_

#include <dmumps_c.h>
#include <vector>
#include <cstring>
#include <iostream>


namespace mumps {


struct problem {

    problem(double* rhs, int n)
    : rhs_{ rhs }, n{ n }
    { }

    problem(std::vector<double>& rhs)
    : rhs_{ rhs.data() }, n{ rhs.size() }
    { }

    void add(int row, int col, double value) {
        rows_.push_back(row);
        cols_.push_back(col);
        values_.push_back(value);
    }

    int nonzero_entries() {
        return values_.size();
    }

    int dofs() {
        return n;
    }

    int* irn() {
        return rows_.data();
    }

    int* jcn() {
        return cols_.data();
    }

    double* a() {
        return values_.data();
    }

    double* rhs() {
        return rhs_;
    }

private:
    std::vector<int> rows_;
    std::vector<int> cols_;
    std::vector<double> values_;
    double* rhs_;
    int n;
};


class solver {
private:
    DMUMPS_STRUC_C id;

    int& icntl(int idx) {
        return id.icntl[idx - 1];
    }
public:

    solver() {
        id.job = -1;
        id.par = 1;
        id.sym = 0;
        id.comm_fortran = 1;


        dmumps_c(&id);

        //ordering metis (5), or pord (4), or AMD (0), AMF (2), QAMD (6)
        icntl(7) = 5;

        // extra space factor
        icntl(14) = 1500;

        //streams
        icntl(1) = 3;
        icntl(2) = 3;
        icntl(3) = 3;
        icntl(4) = 3;
    }

    void print_state(const char* text) const {
        if (id.info[0] != 0) {
            std::cout << text << ":" << std::endl;
            std::cout << "  INFO(1) = " << id.info[0] << std::endl;
            std::cout << "  INFO(2) = " << id.info[1] << std::endl;
            std::cout << "Error: ";
            report_error(std::cout, id.info[0], id.info[1]);
            std::cout << std::endl;
        }
    }

    void solve(problem& problem, const char* output_path = nullptr) {
        id.n = problem.dofs();
        id.nz = problem.nonzero_entries();

        id.irn = problem.irn();
        id.jcn = problem.jcn();
        id.a = problem.a();

        id.rhs = problem.rhs();
        id.nrhs = 1;
        id.lrhs = id.n;

        if (output_path) {
            strcpy(id.write_problem, output_path);
        }

        analyze_();
        factorize_();
        solve_();
    }

    ~solver() {
        id.job = -2;
        dmumps_c(&id);
    }

private:
    void factorize_() {
        id.job = 2;
        dmumps_c(&id);
        print_state("After factorize_()");
    }

    void analyze_() {
        id.job = 1;
        dmumps_c(&id);
        print_state("After analyze_()");
    }

    void solve_() {
        id.job = 3;
        dmumps_c(&id);
        print_state("After solve_()");
    }

    void report_error(std::ostream& os, int info1, int info2) const {
        switch (info1) {
        case -6:
            os << "Matrix singular in structure (rank = " << info2 << ")";
            break;
        case -7:
            os << "Problem of integer workspace allocation (size = " << info2 << ")";
            break;
        case -8:
            os << "Main internal integer workarray is too small";
            break;
        case -9:
            os << "Main internal real/complex workarray is too small (missing = " << info2 << ")";
            break;
        case -10:
            os << "Numerically singular matrix";
            break;
        case -13:
            os << "Problem of workspace allocation (size = " << info2 << ")";
            break;
        }
    }
};


}


#endif /* MUMPS_HPP_ */
