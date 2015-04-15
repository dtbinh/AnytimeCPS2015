/* Produced by CVXGEN, 2015-04-10 21:15:59 -0400.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: testsolver.c. */
/* Description: Basic test harness for solver.c. */
#include "solver.h"
Vars vars;
Params params;
Workspace work;
Settings settings;
#define NUMTESTS 0
int main(int argc, char **argv) {
  int num_iters;
#if (NUMTESTS > 0)
  int i;
  double time;
  double time_per;
#endif
  set_defaults();
  setup_indexing();
  load_default_data();
  /* Solve problem instance for the record. */
  settings.verbose = 1;
  num_iters = solve();
#ifndef ZERO_LIBRARY_MODE
#if (NUMTESTS > 0)
  /* Now solve multiple problem instances for timing purposes. */
  settings.verbose = 0;
  tic();
  for (i = 0; i < NUMTESTS; i++) {
    solve();
  }
  time = tocq();
  printf("Timed %d solves over %.3f seconds.\n", NUMTESTS, time);
  time_per = time / NUMTESTS;
  if (time_per > 1) {
    printf("Actual time taken per solve: %.3g s.\n", time_per);
  } else if (time_per > 1e-3) {
    printf("Actual time taken per solve: %.3g ms.\n", 1e3*time_per);
  } else {
    printf("Actual time taken per solve: %.3g us.\n", 1e6*time_per);
  }
#endif
#endif
  return 0;
}
void load_default_data(void) {
  params.x_0[0] = 0.20319161029830202;
  params.x_0[1] = 0.8325912904724193;
  params.x_0[2] = -0.8363810443482227;
  params.x_0[3] = 0.04331042079065206;
  params.x_0[4] = 1.5717878173906188;
  params.x_0[5] = 1.5851723557337523;
  params.x_ref[0] = -1.497658758144655;
  params.x_ref[1] = -1.171028487447253;
  params.x_ref[2] = -1.7941311867966805;
  params.x_ref[3] = -0.23676062539745413;
  params.x_ref[4] = -1.8804951564857322;
  params.x_ref[5] = -0.17266710242115568;
  /* Make this a diagonal PSD matrix, even though it's not diagonal. */
  params.Q[0] = 1.6491440476147607;
  params.Q[6] = 0;
  params.Q[12] = 0;
  params.Q[18] = 0;
  params.Q[24] = 0;
  params.Q[30] = 0;
  params.Q[1] = 0;
  params.Q[7] = 1.2784872826479754;
  params.Q[13] = 0;
  params.Q[19] = 0;
  params.Q[25] = 0;
  params.Q[31] = 0;
  params.Q[2] = 0;
  params.Q[8] = 0;
  params.Q[14] = 1.6762549019801312;
  params.Q[20] = 0;
  params.Q[26] = 0;
  params.Q[32] = 0;
  params.Q[3] = 0;
  params.Q[9] = 0;
  params.Q[15] = 0;
  params.Q[21] = 1.5908628174163508;
  params.Q[27] = 0;
  params.Q[33] = 0;
  params.Q[4] = 0;
  params.Q[10] = 0;
  params.Q[16] = 0;
  params.Q[22] = 0;
  params.Q[28] = 1.0239818823771654;
  params.Q[34] = 0;
  params.Q[5] = 0;
  params.Q[11] = 0;
  params.Q[17] = 0;
  params.Q[23] = 0;
  params.Q[29] = 0;
  params.Q[35] = 1.5588540879908819;
  /* Make this a diagonal PSD matrix, even though it's not diagonal. */
  params.R[0] = 1.2592524469074653;
  params.R[3] = 0;
  params.R[6] = 0;
  params.R[1] = 0;
  params.R[4] = 1.4151011970100695;
  params.R[7] = 0;
  params.R[2] = 0;
  params.R[5] = 0;
  params.R[8] = 1.2835250817713186;
  /* Make this a diagonal PSD matrix, even though it's not diagonal. */
  params.Q_final[0] = 1.6931379183129964;
  params.Q_final[6] = 0;
  params.Q_final[12] = 0;
  params.Q_final[18] = 0;
  params.Q_final[24] = 0;
  params.Q_final[30] = 0;
  params.Q_final[1] = 0;
  params.Q_final[7] = 1.4404537176707395;
  params.Q_final[13] = 0;
  params.Q_final[19] = 0;
  params.Q_final[25] = 0;
  params.Q_final[31] = 0;
  params.Q_final[2] = 0;
  params.Q_final[8] = 0;
  params.Q_final[14] = 1.1568677384749633;
  params.Q_final[20] = 0;
  params.Q_final[26] = 0;
  params.Q_final[32] = 0;
  params.Q_final[3] = 0;
  params.Q_final[9] = 0;
  params.Q_final[15] = 0;
  params.Q_final[21] = 1.5446490180318446;
  params.Q_final[27] = 0;
  params.Q_final[33] = 0;
  params.Q_final[4] = 0;
  params.Q_final[10] = 0;
  params.Q_final[16] = 0;
  params.Q_final[22] = 0;
  params.Q_final[28] = 1.780314764511367;
  params.Q_final[34] = 0;
  params.Q_final[5] = 0;
  params.Q_final[11] = 0;
  params.Q_final[17] = 0;
  params.Q_final[23] = 0;
  params.Q_final[29] = 0;
  params.Q_final[35] = 1.3063635323761797;
  params.A[0] = -1.1121684642712744;
  params.A[1] = -0.44811496977740495;
  params.A[2] = 1.7455345994417217;
  params.A[3] = 1.9039816898917352;
  params.A[4] = 0.6895347036512547;
  params.A[5] = 1.6113364341535923;
  params.A[6] = 1.383003485172717;
  params.A[7] = -0.48802383468444344;
  params.A[8] = -1.631131964513103;
  params.A[9] = 0.6136436100941447;
  params.A[10] = 0.2313630495538037;
  params.A[11] = -0.5537409477496875;
  params.A[12] = -1.0997819806406723;
  params.A[13] = -0.3739203344950055;
  params.A[14] = -0.12423900520332376;
  params.A[15] = -0.923057686995755;
  params.A[16] = -0.8328289030982696;
  params.A[17] = -0.16925440270808823;
  params.A[18] = 1.442135651787706;
  params.A[19] = 0.34501161787128565;
  params.A[20] = -0.8660485502711608;
  params.A[21] = -0.8880899735055947;
  params.A[22] = -0.1815116979122129;
  params.A[23] = -1.17835862158005;
  params.A[24] = -1.1944851558277074;
  params.A[25] = 0.05614023926976763;
  params.A[26] = -1.6510825248767813;
  params.A[27] = -0.06565787059365391;
  params.A[28] = -0.5512951504486665;
  params.A[29] = 0.8307464872626844;
  params.A[30] = 0.9869848924080182;
  params.A[31] = 0.7643716874230573;
  params.A[32] = 0.7567216550196565;
  params.A[33] = -0.5055995034042868;
  params.A[34] = 0.6725392189410702;
  params.A[35] = -0.6406053441727284;
  params.B[0] = 0.29117547947550015;
  params.B[1] = -0.6967713677405021;
  params.B[2] = -0.21941980294587182;
  params.B[3] = -1.753884276680243;
  params.B[4] = -1.0292983112626475;
  params.B[5] = 1.8864104246942706;
  params.B[6] = -1.077663182579704;
  params.B[7] = 0.7659100437893209;
  params.B[8] = 0.6019074328549583;
  params.B[9] = 0.8957565577499285;
  params.B[10] = -0.09964555746227477;
  params.B[11] = 0.38665509840745127;
  params.B[12] = -1.7321223042686946;
  params.B[13] = -1.7097514487110663;
  params.B[14] = -1.2040958948116867;
  params.B[15] = -1.3925560119658358;
  params.B[16] = -1.5995826216742213;
  params.B[17] = -1.4828245415645833;
  params.u_limit[0] = 1.106555463615307;
  params.u_limit[1] = 0.3756296498477565;
  params.u_limit[2] = 1.9042024860624165;
  params.x_limit[0] = 1.3632235576148533;
  params.x_limit[1] = 1.0820393467195424;
  params.x_limit[2] = 1.4143612016157954;
  params.x_limit[3] = 0.5277733419050268;
  params.x_limit[4] = 1.8534513685074556;
  params.x_limit[5] = 1.6783861155999413;
}
