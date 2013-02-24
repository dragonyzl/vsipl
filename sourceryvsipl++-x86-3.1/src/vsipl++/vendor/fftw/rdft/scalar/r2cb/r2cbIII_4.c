/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * See the file COPYING for license information.
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Mon Nov 10 20:57:38 EST 2008 */

#include "codelet-rdft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_r2cb -fma -reorder-insns -schedule-for-pipeline -compact -variables 4 -pipeline-latency 4 -sign 1 -n 4 -name r2cbIII_4 -dft-III -include r2cbIII.h */

/*
 * This function contains 6 FP additions, 4 FP multiplications,
 * (or, 6 additions, 4 multiplications, 0 fused multiply/add),
 * 9 stack variables, 2 constants, and 8 memory accesses
 */
#include "r2cbIII.h"

static void r2cbIII_4(R *R0, R *R1, R *Cr, R *Ci, stride rs, stride csr, stride csi, INT v, INT ivs, INT ovs)
{
     DK(KP1_414213562, +1.414213562373095048801688724209698078569671875);
     DK(KP2_000000000, +2.000000000000000000000000000000000000000000000);
     INT i;
     for (i = v; i > 0; i = i - 1, R0 = R0 + ovs, R1 = R1 + ovs, Cr = Cr + ivs, Ci = Ci + ivs, MAKE_VOLATILE_STRIDE(rs), MAKE_VOLATILE_STRIDE(csr), MAKE_VOLATILE_STRIDE(csi)) {
	  E T1, T2, T4, T5, T3, T6;
	  T1 = Cr[0];
	  T2 = Cr[WS(csr, 1)];
	  T4 = Ci[0];
	  T5 = Ci[WS(csi, 1)];
	  R0[0] = KP2_000000000 * (T1 + T2);
	  T3 = T1 - T2;
	  R0[WS(rs, 1)] = KP2_000000000 * (T5 - T4);
	  T6 = T4 + T5;
	  R1[WS(rs, 1)] = -(KP1_414213562 * (T3 + T6));
	  R1[0] = KP1_414213562 * (T3 - T6);
     }
}

static const kr2c_desc desc = { 4, "r2cbIII_4", {6, 4, 0, 0}, &GENUS };

void X(codelet_r2cbIII_4) (planner *p) {
     X(kr2c_register) (p, r2cbIII_4, &desc);
}

#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_r2cb -compact -variables 4 -pipeline-latency 4 -sign 1 -n 4 -name r2cbIII_4 -dft-III -include r2cbIII.h */

/*
 * This function contains 6 FP additions, 4 FP multiplications,
 * (or, 6 additions, 4 multiplications, 0 fused multiply/add),
 * 9 stack variables, 2 constants, and 8 memory accesses
 */
#include "r2cbIII.h"

static void r2cbIII_4(R *R0, R *R1, R *Cr, R *Ci, stride rs, stride csr, stride csi, INT v, INT ivs, INT ovs)
{
     DK(KP1_414213562, +1.414213562373095048801688724209698078569671875);
     DK(KP2_000000000, +2.000000000000000000000000000000000000000000000);
     INT i;
     for (i = v; i > 0; i = i - 1, R0 = R0 + ovs, R1 = R1 + ovs, Cr = Cr + ivs, Ci = Ci + ivs, MAKE_VOLATILE_STRIDE(rs), MAKE_VOLATILE_STRIDE(csr), MAKE_VOLATILE_STRIDE(csi)) {
	  E T1, T2, T3, T4, T5, T6;
	  T1 = Cr[0];
	  T2 = Cr[WS(csr, 1)];
	  T3 = T1 - T2;
	  T4 = Ci[0];
	  T5 = Ci[WS(csi, 1)];
	  T6 = T4 + T5;
	  R0[0] = KP2_000000000 * (T1 + T2);
	  R0[WS(rs, 1)] = KP2_000000000 * (T5 - T4);
	  R1[0] = KP1_414213562 * (T3 - T6);
	  R1[WS(rs, 1)] = -(KP1_414213562 * (T3 + T6));
     }
}

static const kr2c_desc desc = { 4, "r2cbIII_4", {6, 4, 0, 0}, &GENUS };

void X(codelet_r2cbIII_4) (planner *p) {
     X(kr2c_register) (p, r2cbIII_4, &desc);
}

#endif				/* HAVE_FMA */