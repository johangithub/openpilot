#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with sympy 1.9                        *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_7361038110530370221) {
   out_7361038110530370221[0] = delta_x[0] + nom_x[0];
   out_7361038110530370221[1] = delta_x[1] + nom_x[1];
   out_7361038110530370221[2] = delta_x[2] + nom_x[2];
   out_7361038110530370221[3] = delta_x[3] + nom_x[3];
   out_7361038110530370221[4] = delta_x[4] + nom_x[4];
   out_7361038110530370221[5] = delta_x[5] + nom_x[5];
   out_7361038110530370221[6] = delta_x[6] + nom_x[6];
   out_7361038110530370221[7] = delta_x[7] + nom_x[7];
   out_7361038110530370221[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6642685734919517258) {
   out_6642685734919517258[0] = -nom_x[0] + true_x[0];
   out_6642685734919517258[1] = -nom_x[1] + true_x[1];
   out_6642685734919517258[2] = -nom_x[2] + true_x[2];
   out_6642685734919517258[3] = -nom_x[3] + true_x[3];
   out_6642685734919517258[4] = -nom_x[4] + true_x[4];
   out_6642685734919517258[5] = -nom_x[5] + true_x[5];
   out_6642685734919517258[6] = -nom_x[6] + true_x[6];
   out_6642685734919517258[7] = -nom_x[7] + true_x[7];
   out_6642685734919517258[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2530205897380259158) {
   out_2530205897380259158[0] = 1.0;
   out_2530205897380259158[1] = 0;
   out_2530205897380259158[2] = 0;
   out_2530205897380259158[3] = 0;
   out_2530205897380259158[4] = 0;
   out_2530205897380259158[5] = 0;
   out_2530205897380259158[6] = 0;
   out_2530205897380259158[7] = 0;
   out_2530205897380259158[8] = 0;
   out_2530205897380259158[9] = 0;
   out_2530205897380259158[10] = 1.0;
   out_2530205897380259158[11] = 0;
   out_2530205897380259158[12] = 0;
   out_2530205897380259158[13] = 0;
   out_2530205897380259158[14] = 0;
   out_2530205897380259158[15] = 0;
   out_2530205897380259158[16] = 0;
   out_2530205897380259158[17] = 0;
   out_2530205897380259158[18] = 0;
   out_2530205897380259158[19] = 0;
   out_2530205897380259158[20] = 1.0;
   out_2530205897380259158[21] = 0;
   out_2530205897380259158[22] = 0;
   out_2530205897380259158[23] = 0;
   out_2530205897380259158[24] = 0;
   out_2530205897380259158[25] = 0;
   out_2530205897380259158[26] = 0;
   out_2530205897380259158[27] = 0;
   out_2530205897380259158[28] = 0;
   out_2530205897380259158[29] = 0;
   out_2530205897380259158[30] = 1.0;
   out_2530205897380259158[31] = 0;
   out_2530205897380259158[32] = 0;
   out_2530205897380259158[33] = 0;
   out_2530205897380259158[34] = 0;
   out_2530205897380259158[35] = 0;
   out_2530205897380259158[36] = 0;
   out_2530205897380259158[37] = 0;
   out_2530205897380259158[38] = 0;
   out_2530205897380259158[39] = 0;
   out_2530205897380259158[40] = 1.0;
   out_2530205897380259158[41] = 0;
   out_2530205897380259158[42] = 0;
   out_2530205897380259158[43] = 0;
   out_2530205897380259158[44] = 0;
   out_2530205897380259158[45] = 0;
   out_2530205897380259158[46] = 0;
   out_2530205897380259158[47] = 0;
   out_2530205897380259158[48] = 0;
   out_2530205897380259158[49] = 0;
   out_2530205897380259158[50] = 1.0;
   out_2530205897380259158[51] = 0;
   out_2530205897380259158[52] = 0;
   out_2530205897380259158[53] = 0;
   out_2530205897380259158[54] = 0;
   out_2530205897380259158[55] = 0;
   out_2530205897380259158[56] = 0;
   out_2530205897380259158[57] = 0;
   out_2530205897380259158[58] = 0;
   out_2530205897380259158[59] = 0;
   out_2530205897380259158[60] = 1.0;
   out_2530205897380259158[61] = 0;
   out_2530205897380259158[62] = 0;
   out_2530205897380259158[63] = 0;
   out_2530205897380259158[64] = 0;
   out_2530205897380259158[65] = 0;
   out_2530205897380259158[66] = 0;
   out_2530205897380259158[67] = 0;
   out_2530205897380259158[68] = 0;
   out_2530205897380259158[69] = 0;
   out_2530205897380259158[70] = 1.0;
   out_2530205897380259158[71] = 0;
   out_2530205897380259158[72] = 0;
   out_2530205897380259158[73] = 0;
   out_2530205897380259158[74] = 0;
   out_2530205897380259158[75] = 0;
   out_2530205897380259158[76] = 0;
   out_2530205897380259158[77] = 0;
   out_2530205897380259158[78] = 0;
   out_2530205897380259158[79] = 0;
   out_2530205897380259158[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8104591686044368808) {
   out_8104591686044368808[0] = state[0];
   out_8104591686044368808[1] = state[1];
   out_8104591686044368808[2] = state[2];
   out_8104591686044368808[3] = state[3];
   out_8104591686044368808[4] = state[4];
   out_8104591686044368808[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8104591686044368808[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8104591686044368808[7] = state[7];
   out_8104591686044368808[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2827006867786055650) {
   out_2827006867786055650[0] = 1;
   out_2827006867786055650[1] = 0;
   out_2827006867786055650[2] = 0;
   out_2827006867786055650[3] = 0;
   out_2827006867786055650[4] = 0;
   out_2827006867786055650[5] = 0;
   out_2827006867786055650[6] = 0;
   out_2827006867786055650[7] = 0;
   out_2827006867786055650[8] = 0;
   out_2827006867786055650[9] = 0;
   out_2827006867786055650[10] = 1;
   out_2827006867786055650[11] = 0;
   out_2827006867786055650[12] = 0;
   out_2827006867786055650[13] = 0;
   out_2827006867786055650[14] = 0;
   out_2827006867786055650[15] = 0;
   out_2827006867786055650[16] = 0;
   out_2827006867786055650[17] = 0;
   out_2827006867786055650[18] = 0;
   out_2827006867786055650[19] = 0;
   out_2827006867786055650[20] = 1;
   out_2827006867786055650[21] = 0;
   out_2827006867786055650[22] = 0;
   out_2827006867786055650[23] = 0;
   out_2827006867786055650[24] = 0;
   out_2827006867786055650[25] = 0;
   out_2827006867786055650[26] = 0;
   out_2827006867786055650[27] = 0;
   out_2827006867786055650[28] = 0;
   out_2827006867786055650[29] = 0;
   out_2827006867786055650[30] = 1;
   out_2827006867786055650[31] = 0;
   out_2827006867786055650[32] = 0;
   out_2827006867786055650[33] = 0;
   out_2827006867786055650[34] = 0;
   out_2827006867786055650[35] = 0;
   out_2827006867786055650[36] = 0;
   out_2827006867786055650[37] = 0;
   out_2827006867786055650[38] = 0;
   out_2827006867786055650[39] = 0;
   out_2827006867786055650[40] = 1;
   out_2827006867786055650[41] = 0;
   out_2827006867786055650[42] = 0;
   out_2827006867786055650[43] = 0;
   out_2827006867786055650[44] = 0;
   out_2827006867786055650[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2827006867786055650[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2827006867786055650[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2827006867786055650[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2827006867786055650[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2827006867786055650[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2827006867786055650[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2827006867786055650[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2827006867786055650[53] = -9.8000000000000007*dt;
   out_2827006867786055650[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2827006867786055650[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2827006867786055650[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2827006867786055650[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2827006867786055650[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2827006867786055650[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2827006867786055650[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2827006867786055650[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2827006867786055650[62] = 0;
   out_2827006867786055650[63] = 0;
   out_2827006867786055650[64] = 0;
   out_2827006867786055650[65] = 0;
   out_2827006867786055650[66] = 0;
   out_2827006867786055650[67] = 0;
   out_2827006867786055650[68] = 0;
   out_2827006867786055650[69] = 0;
   out_2827006867786055650[70] = 1;
   out_2827006867786055650[71] = 0;
   out_2827006867786055650[72] = 0;
   out_2827006867786055650[73] = 0;
   out_2827006867786055650[74] = 0;
   out_2827006867786055650[75] = 0;
   out_2827006867786055650[76] = 0;
   out_2827006867786055650[77] = 0;
   out_2827006867786055650[78] = 0;
   out_2827006867786055650[79] = 0;
   out_2827006867786055650[80] = 1;
}
void h_25(double *state, double *unused, double *out_7566196993710386620) {
   out_7566196993710386620[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6410871014676703632) {
   out_6410871014676703632[0] = 0;
   out_6410871014676703632[1] = 0;
   out_6410871014676703632[2] = 0;
   out_6410871014676703632[3] = 0;
   out_6410871014676703632[4] = 0;
   out_6410871014676703632[5] = 0;
   out_6410871014676703632[6] = 1;
   out_6410871014676703632[7] = 0;
   out_6410871014676703632[8] = 0;
}
void h_24(double *state, double *unused, double *out_7879487054421198263) {
   out_7879487054421198263[0] = state[4];
   out_7879487054421198263[1] = state[5];
}
void H_24(double *state, double *unused, double *out_8477947460230524848) {
   out_8477947460230524848[0] = 0;
   out_8477947460230524848[1] = 0;
   out_8477947460230524848[2] = 0;
   out_8477947460230524848[3] = 0;
   out_8477947460230524848[4] = 1;
   out_8477947460230524848[5] = 0;
   out_8477947460230524848[6] = 0;
   out_8477947460230524848[7] = 0;
   out_8477947460230524848[8] = 0;
   out_8477947460230524848[9] = 0;
   out_8477947460230524848[10] = 0;
   out_8477947460230524848[11] = 0;
   out_8477947460230524848[12] = 0;
   out_8477947460230524848[13] = 0;
   out_8477947460230524848[14] = 1;
   out_8477947460230524848[15] = 0;
   out_8477947460230524848[16] = 0;
   out_8477947460230524848[17] = 0;
}
void h_30(double *state, double *unused, double *out_7291002931425880731) {
   out_7291002931425880731[0] = state[4];
}
void H_30(double *state, double *unused, double *out_1883174684549095434) {
   out_1883174684549095434[0] = 0;
   out_1883174684549095434[1] = 0;
   out_1883174684549095434[2] = 0;
   out_1883174684549095434[3] = 0;
   out_1883174684549095434[4] = 1;
   out_1883174684549095434[5] = 0;
   out_1883174684549095434[6] = 0;
   out_1883174684549095434[7] = 0;
   out_1883174684549095434[8] = 0;
}
void h_26(double *state, double *unused, double *out_1114653888218345922) {
   out_1114653888218345922[0] = state[7];
}
void H_26(double *state, double *unused, double *out_2669367695802647408) {
   out_2669367695802647408[0] = 0;
   out_2669367695802647408[1] = 0;
   out_2669367695802647408[2] = 0;
   out_2669367695802647408[3] = 0;
   out_2669367695802647408[4] = 0;
   out_2669367695802647408[5] = 0;
   out_2669367695802647408[6] = 0;
   out_2669367695802647408[7] = 1;
   out_2669367695802647408[8] = 0;
}
void h_27(double *state, double *unused, double *out_4102018324380578519) {
   out_4102018324380578519[0] = state[3];
}
void H_27(double *state, double *unused, double *out_291588627251329477) {
   out_291588627251329477[0] = 0;
   out_291588627251329477[1] = 0;
   out_291588627251329477[2] = 0;
   out_291588627251329477[3] = 1;
   out_291588627251329477[4] = 0;
   out_291588627251329477[5] = 0;
   out_291588627251329477[6] = 0;
   out_291588627251329477[7] = 0;
   out_291588627251329477[8] = 0;
}
void h_29(double *state, double *unused, double *out_6687687046749403214) {
   out_6687687046749403214[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2393406028863487618) {
   out_2393406028863487618[0] = 0;
   out_2393406028863487618[1] = 1;
   out_2393406028863487618[2] = 0;
   out_2393406028863487618[3] = 0;
   out_2393406028863487618[4] = 0;
   out_2393406028863487618[5] = 0;
   out_2393406028863487618[6] = 0;
   out_2393406028863487618[7] = 0;
   out_2393406028863487618[8] = 0;
}
void h_28(double *state, double *unused, double *out_860361673300714713) {
   out_860361673300714713[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2688992988206042956) {
   out_2688992988206042956[0] = 1;
   out_2688992988206042956[1] = 0;
   out_2688992988206042956[2] = 0;
   out_2688992988206042956[3] = 0;
   out_2688992988206042956[4] = 0;
   out_2688992988206042956[5] = 0;
   out_2688992988206042956[6] = 0;
   out_2688992988206042956[7] = 0;
   out_2688992988206042956[8] = 0;
}
void h_31(double *state, double *unused, double *out_7243097551745142646) {
   out_7243097551745142646[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2043159593569295932) {
   out_2043159593569295932[0] = 0;
   out_2043159593569295932[1] = 0;
   out_2043159593569295932[2] = 0;
   out_2043159593569295932[3] = 0;
   out_2043159593569295932[4] = 0;
   out_2043159593569295932[5] = 0;
   out_2043159593569295932[6] = 0;
   out_2043159593569295932[7] = 0;
   out_2043159593569295932[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_7361038110530370221) {
  err_fun(nom_x, delta_x, out_7361038110530370221);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6642685734919517258) {
  inv_err_fun(nom_x, true_x, out_6642685734919517258);
}
void car_H_mod_fun(double *state, double *out_2530205897380259158) {
  H_mod_fun(state, out_2530205897380259158);
}
void car_f_fun(double *state, double dt, double *out_8104591686044368808) {
  f_fun(state,  dt, out_8104591686044368808);
}
void car_F_fun(double *state, double dt, double *out_2827006867786055650) {
  F_fun(state,  dt, out_2827006867786055650);
}
void car_h_25(double *state, double *unused, double *out_7566196993710386620) {
  h_25(state, unused, out_7566196993710386620);
}
void car_H_25(double *state, double *unused, double *out_6410871014676703632) {
  H_25(state, unused, out_6410871014676703632);
}
void car_h_24(double *state, double *unused, double *out_7879487054421198263) {
  h_24(state, unused, out_7879487054421198263);
}
void car_H_24(double *state, double *unused, double *out_8477947460230524848) {
  H_24(state, unused, out_8477947460230524848);
}
void car_h_30(double *state, double *unused, double *out_7291002931425880731) {
  h_30(state, unused, out_7291002931425880731);
}
void car_H_30(double *state, double *unused, double *out_1883174684549095434) {
  H_30(state, unused, out_1883174684549095434);
}
void car_h_26(double *state, double *unused, double *out_1114653888218345922) {
  h_26(state, unused, out_1114653888218345922);
}
void car_H_26(double *state, double *unused, double *out_2669367695802647408) {
  H_26(state, unused, out_2669367695802647408);
}
void car_h_27(double *state, double *unused, double *out_4102018324380578519) {
  h_27(state, unused, out_4102018324380578519);
}
void car_H_27(double *state, double *unused, double *out_291588627251329477) {
  H_27(state, unused, out_291588627251329477);
}
void car_h_29(double *state, double *unused, double *out_6687687046749403214) {
  h_29(state, unused, out_6687687046749403214);
}
void car_H_29(double *state, double *unused, double *out_2393406028863487618) {
  H_29(state, unused, out_2393406028863487618);
}
void car_h_28(double *state, double *unused, double *out_860361673300714713) {
  h_28(state, unused, out_860361673300714713);
}
void car_H_28(double *state, double *unused, double *out_2688992988206042956) {
  H_28(state, unused, out_2688992988206042956);
}
void car_h_31(double *state, double *unused, double *out_7243097551745142646) {
  h_31(state, unused, out_7243097551745142646);
}
void car_H_31(double *state, double *unused, double *out_2043159593569295932) {
  H_31(state, unused, out_2043159593569295932);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_init(car);
