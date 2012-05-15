#if EEL_F_SIZE == 8

void nseel_asm_1pdd(void)
{

  __asm__( 
    "addis r5, 0, 0xdead\n" 
    "ori r5, r5, 0xbeef\n"  
    "mtctr r5\n" 
    "subi r1, r1, 64\n" 
    "bctrl\n" 
    "addi r1, r1, 64\n" 
   :: );
}
void nseel_asm_1pdd_end(void){}

void nseel_asm_2pdd(void)
{

  __asm__( 
    "addis r7, 0, 0xdead\n" 
    "ori r7, r7, 0xbeef\n"  
    "fmr f2, f1\n" 
    "lfd f1, 0(r14)\n" 
    "mtctr r7\n" 
    "subi r1, r1, 64\n" 
    "bctrl\n" 
    "addi r1, r1, 64\n" 
   :: );
};
void nseel_asm_2pdd_end(void){}

void nseel_asm_2pdds(void)
{
  __asm__( 
    "addis r5, 0, 0xdead\n" 
    "ori r5, r5, 0xbeef\n"  
    "fmr f2, f1\n" 
    "lfd f1, 0(r14)\n" 
    "mtctr r5\n" 
    "subi r1, r1, 64\n" 
    "bctrl\n" 
    "addi r1, r1, 64\n" 
    "stfd f1, 0(r14)\n" 
    "mr r3, r14\n" 
   :: );
}
void nseel_asm_2pdds_end(void){}

#else // 32 bit floating point calls

#error no 32 bit float support

#endif

//---------------------------------------------------------------------------------------------------------------



// do nothing, eh
void nseel_asm_exec2(void)
{
}
void nseel_asm_exec2_end(void) { }



void nseel_asm_invsqrt(void)
{
  __asm__(
   "frsqrte f1, f1\n" // less accurate than our x86 equivilent, but invsqrt() is inherently inaccurate anyway
  );
}
void nseel_asm_invsqrt_end(void) {}



//---------------------------------------------------------------------------------------------------------------
void nseel_asm_sqr(void)
{
  __asm__(
   "fmul f1, f1, f1\n"
  );
}
void nseel_asm_sqr_end(void) {}


//---------------------------------------------------------------------------------------------------------------
void nseel_asm_abs(void)
{
  __asm__(
   "fabs f1, f1\n"
  );
}
void nseel_asm_abs_end(void) {}


//---------------------------------------------------------------------------------------------------------------
void nseel_asm_assign(void)
{
  __asm__(
   "lfd f1, 0(r3)\n"
   "mr r3, r14\n"
   "stfd f1, 0(r14)\n"
  );
}
void nseel_asm_assign_end(void) {}
//
//---------------------------------------------------------------------------------------------------------------
void nseel_asm_assign_fromfp(void)
{
  __asm__(
   "mr r3, r14\n"
   "stfd f1, 0(r14)\n"
  );
}
void nseel_asm_assign_fromfp_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_add(void)
{
  __asm__(
   "lfd f2, 0(r14)\n"
   "fadd f1, f1, f2\n"
  );
}
void nseel_asm_add_end(void) {}

void nseel_asm_add_op(void)
{
  __asm__(
   "lfd f2, 0(r14)\n"
   "fadd f1, f1, f2\n"
   "mr r3, r14\n"
   "stfd f1, 0(r14)\n"
  );
}
void nseel_asm_add_op_end(void) {}


//---------------------------------------------------------------------------------------------------------------
void nseel_asm_sub(void)
{
  __asm__(
   "lfd f2, 0(r14)\n"
   "fsub f1, f2, f1\n"
  );
}
void nseel_asm_sub_end(void) {}

void nseel_asm_sub_op(void)
{
  __asm__(
   "lfd f2, 0(r14)\n"
   "fsub f1, f2, f1\n"
   "mr r3, r14\n"
   "stfd f1, 0(r14)\n"
  );
}
void nseel_asm_sub_op_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_mul(void)
{
  __asm__(
   "lfd f2, 0(r14)\n"
   "fmul f1, f2, f1\n"
  );
}
void nseel_asm_mul_end(void) {}

void nseel_asm_mul_op(void)
{
  __asm__(
   "lfd f2, 0(r14)\n"
   "fmul f1, f2, f1\n"
   "mr r3, r14\n"
   "stfd f1, 0(r14)\n"
  );
}
void nseel_asm_mul_op_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_div(void)
{
  __asm__(
   "lfd f2, 0(r14)\n"
   "fdiv f1, f2, f1\n"
  );
}
void nseel_asm_div_end(void) {}

void nseel_asm_div_op(void)
{
  __asm__(
   "lfd f2, 0(r14)\n"
   "fdiv f1, f2, f1\n"
   "mr r3, r14\n"
   "stfd f1, 0(r14)\n"
  );
}
void nseel_asm_div_op_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_mod(void)
{
  __asm__(
   "lfd f2, 0(r14)\n"
   "fabs f1, f1\n"
   "fabs f2, f2\n"
   "fctiwz f1, f1\n"
   "fctiwz f2, f2\n"
   "stfd f1, 8(r16)\n"
   "stfd f2, 16(r16)\n"
   "lwz r10, 12(r16)\n"
   "lwz r11, 20(r16)\n" //r11 and r12 have the integers

   "divw r12, r11, r10\n"
   "mullw r12, r12, r10\n"
   "subf r10, r12, r11\n"

   "addis r11, 0, 0x4330\n"
   "addis r12, 0, 0x8000\n"
   "xoris r10, r10, 0x8000\n"
   "stw r11, 8(r16)\n"   // 0x43300000
   "stw r10, 12(r16)\n"  // our integer sign flipped
   "stw r11, 16(r16)\n"  // 0x43300000
   "stw r12, 20(r16)\n"  // 0x80000000
   "lfd f1, 8(r16)\n"
   "lfd f2, 16(r16)\n"
   "fsub f1, f1, f2\n"
  );
}
void nseel_asm_mod_end(void) {}

void nseel_asm_shl(void)
{
  __asm__(
   "lfd f2, 0(r14)\n"
   "fctiwz f1, f1\n"
   "fctiwz f2, f2\n"
   "stfd f1, 8(r16)\n"
   "stfd f2, 16(r16)\n"
   "lwz r10, 12(r16)\n"
   "lwz r11, 20(r16)\n" //r11 and r12 have the integers
   "slw r10, r11, r10\n" // r10 has the result
   "addis r11, 0, 0x4330\n"
   "addis r12, 0, 0x8000\n"
   "xoris r10, r10, 0x8000\n"
   "stw r11, 8(r16)\n"   // 0x43300000
   "stw r10, 12(r16)\n"  // our integer sign flipped
   "stw r11, 16(r16)\n"  // 0x43300000
   "stw r12, 20(r16)\n"  // 0x80000000
   "lfd f1, 8(r16)\n"
   "lfd f2, 16(r16)\n"
   "fsub f1, f1, f2\n"
  );
}
void nseel_asm_shl_end(void) {}

void nseel_asm_shr(void)
{
  __asm__(
   "lfd f2, 0(r14)\n"
   "fctiwz f1, f1\n"
   "fctiwz f2, f2\n"
   "stfd f1, 8(r16)\n"
   "stfd f2, 16(r16)\n"
   "lwz r10, 12(r16)\n"
   "lwz r11, 20(r16)\n" //r11 and r12 have the integers
   "sraw r10, r11, r10\n" // r10 has the result
   "addis r11, 0, 0x4330\n"
   "addis r12, 0, 0x8000\n"
   "xoris r10, r10, 0x8000\n"
   "stw r11, 8(r16)\n"   // 0x43300000
   "stw r10, 12(r16)\n"  // our integer sign flipped
   "stw r11, 16(r16)\n"  // 0x43300000
   "stw r12, 20(r16)\n"  // 0x80000000
   "lfd f1, 8(r16)\n"
   "lfd f2, 16(r16)\n"
   "fsub f1, f1, f2\n"
  );
}
void nseel_asm_shr_end(void) {}

void nseel_asm_mod_op(void)
{

  __asm__(
   "lfd f2, 0(r14)\n"
   "fabs f1, f1\n"
   "fabs f2, f2\n"
   "fctiwz f1, f1\n"
   "fctiwz f2, f2\n"
   "stfd f1, 8(r16)\n"
   "stfd f2, 16(r16)\n"
   "lwz r10, 12(r16)\n"
   "lwz r11, 20(r16)\n" //r11 and r12 have the integers

   "divw r12, r11, r10\n"
   "mullw r12, r12, r10\n"
   "subf r10, r12, r11\n"

   "addis r11, 0, 0x4330\n"
   "addis r12, 0, 0x8000\n"
   "xoris r10, r10, 0x8000\n"
   "stw r11, 8(r16)\n"   // 0x43300000
   "stw r10, 12(r16)\n"  // our integer sign flipped
   "stw r11, 16(r16)\n"  // 0x43300000
   "stw r12, 20(r16)\n"  // 0x80000000
   "lfd f1, 8(r16)\n"
   "lfd f2, 16(r16)\n"
   "fsub f1, f1, f2\n"
   "mr r3, r14\n"
   "stfd f1, 0(r14)\n"
  );

}
void nseel_asm_mod_op_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_or(void)
{
  __asm__(
   "lfd f2, 0(r14)\n"
   "fctiwz f1, f1\n"
   "fctiwz f2, f2\n"
   "stfd f1, 8(r16)\n"
   "stfd f2, 16(r16)\n"
   "lwz r10, 12(r16)\n"
   "lwz r11, 20(r16)\n" //r11 and r12 have the integers
   "or r10, r10, r11\n" // r10 has the result
   "addis r11, 0, 0x4330\n"
   "addis r12, 0, 0x8000\n"
   "xoris r10, r10, 0x8000\n"
   "stw r11, 8(r16)\n"   // 0x43300000
   "stw r10, 12(r16)\n"  // our integer sign flipped
   "stw r11, 16(r16)\n"  // 0x43300000
   "stw r12, 20(r16)\n"  // 0x80000000
   "lfd f1, 8(r16)\n"
   "lfd f2, 16(r16)\n"
   "fsub f1, f1, f2\n"
  );
}
void nseel_asm_or_end(void) {}

void nseel_asm_or0(void)
{
  __asm__(
   "addis r11, 0, 0x4330\n"
   "fctiwz f1, f1\n"
   "addis r12, 0, 0x8000\n"
   "stfd f1, 8(r16)\n"
   "lwz r10, 12(r16)\n"
   "xoris r10, r10, 0x8000\n"
   "stw r11, 8(r16)\n"   // 0x43300000
   "stw r10, 12(r16)\n"  // our integer sign flipped
   "stw r11, 16(r16)\n"  // 0x43300000
   "stw r12, 20(r16)\n"  // 0x80000000
   "lfd f1, 8(r16)\n"
   "lfd f2, 16(r16)\n"
   "fsub f1, f1, f2\n"
  );
}
void nseel_asm_or0_end(void) {}

void nseel_asm_or_op(void)
{
  __asm__(
   "lfd f2, 0(r14)\n"
   "fctiwz f1, f1\n"
   "fctiwz f2, f2\n"
   "stfd f1, 8(r16)\n"
   "stfd f2, 16(r16)\n"
   "lwz r10, 12(r16)\n"
   "lwz r11, 20(r16)\n" //r11 and r12 have the integers
   "or r10, r10, r11\n" // r10 has the result
   "addis r11, 0, 0x4330\n"
   "addis r12, 0, 0x8000\n"
   "xoris r10, r10, 0x8000\n"
   "stw r11, 8(r16)\n"   // 0x43300000
   "stw r10, 12(r16)\n"  // our integer sign flipped
   "stw r11, 16(r16)\n"  // 0x43300000
   "stw r12, 20(r16)\n"  // 0x80000000
   "lfd f1, 8(r16)\n"
   "lfd f2, 16(r16)\n"
   "fsub f1, f1, f2\n"
   "mr r3, r14\n"
   "stfd f1, 0(r14)\n"
  );
}
void nseel_asm_or_op_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_xor(void)
{
  __asm__(
   "lfd f2, 0(r14)\n"
   "fctiwz f1, f1\n"
   "fctiwz f2, f2\n"
   "stfd f1, 8(r16)\n"
   "stfd f2, 16(r16)\n"
   "lwz r10, 12(r16)\n"
   "lwz r11, 20(r16)\n" //r11 and r12 have the integers
   "xor r10, r10, r11\n" // r10 has the result
   "addis r11, 0, 0x4330\n"
   "addis r12, 0, 0x8000\n"
   "xoris r10, r10, 0x8000\n"
   "stw r11, 8(r16)\n"   // 0x43300000
   "stw r10, 12(r16)\n"  // our integer sign flipped
   "stw r11, 16(r16)\n"  // 0x43300000
   "stw r12, 20(r16)\n"  // 0x80000000
   "lfd f1, 8(r16)\n"
   "lfd f2, 16(r16)\n"
   "fsub f1, f1, f2\n"
  );
}
void nseel_asm_xor_end(void) {}

void nseel_asm_xor_op(void)
{
  __asm__(
   "lfd f2, 0(r14)\n"
   "fctiwz f1, f1\n"
   "fctiwz f2, f2\n"
   "stfd f1, 8(r16)\n"
   "stfd f2, 16(r16)\n"
   "lwz r10, 12(r16)\n"
   "lwz r11, 20(r16)\n" //r11 and r12 have the integers
   "xor r10, r10, r11\n" // r10 has the result
   "addis r11, 0, 0x4330\n"
   "addis r12, 0, 0x8000\n"
   "xoris r10, r10, 0x8000\n"
   "stw r11, 8(r16)\n"   // 0x43300000
   "stw r10, 12(r16)\n"  // our integer sign flipped
   "stw r11, 16(r16)\n"  // 0x43300000
   "stw r12, 20(r16)\n"  // 0x80000000
   "lfd f1, 8(r16)\n"
   "lfd f2, 16(r16)\n"
   "fsub f1, f1, f2\n"
   "mr r3, r14\n"
   "stfd f1, 0(r14)\n"
  );
}
void nseel_asm_xor_op_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_and(void)
{
  __asm__(
   "lfd f2, 0(r14)\n"
   "fctiwz f1, f1\n"
   "fctiwz f2, f2\n"
   "stfd f1, 8(r16)\n"
   "stfd f2, 16(r16)\n"
   "lwz r10, 12(r16)\n"
   "lwz r11, 20(r16)\n" //r11 and r12 have the integers
   "and r10, r10, r11\n" // r10 has the result
   "addis r11, 0, 0x4330\n"
   "addis r12, 0, 0x8000\n"
   "xoris r10, r10, 0x8000\n"
   "stw r11, 8(r16)\n"   // 0x43300000
   "stw r10, 12(r16)\n"  // our integer sign flipped
   "stw r11, 16(r16)\n"  // 0x43300000
   "stw r12, 20(r16)\n"  // 0x80000000
   "lfd f1, 8(r16)\n"
   "lfd f2, 16(r16)\n"
   "fsub f1, f1, f2\n"
  );}
void nseel_asm_and_end(void) {}

void nseel_asm_and_op(void)
{
  __asm__(
   "lfd f2, 0(r14)\n"
   "fctiwz f1, f1\n"
   "fctiwz f2, f2\n"
   "stfd f1, 8(r16)\n"
   "stfd f2, 16(r16)\n"
   "lwz r10, 12(r16)\n"
   "lwz r11, 20(r16)\n" //r11 and r12 have the integers
   "and r10, r10, r11\n" // r10 has the result
   "addis r11, 0, 0x4330\n"
   "addis r12, 0, 0x8000\n"
   "xoris r10, r10, 0x8000\n"
   "stw r11, 8(r16)\n"   // 0x43300000
   "stw r10, 12(r16)\n"  // our integer sign flipped
   "stw r11, 16(r16)\n"  // 0x43300000
   "stw r12, 20(r16)\n"  // 0x80000000
   "lfd f1, 8(r16)\n"
   "lfd f2, 16(r16)\n"
   "fsub f1, f1, f2\n"
   "mr r3, r14\n"
   "stfd f1, 0(r14)\n"
  );
}
void nseel_asm_and_op_end(void) {}


//---------------------------------------------------------------------------------------------------------------
void nseel_asm_uplus(void) // this is the same as doing nothing, it seems
{
}
void nseel_asm_uplus_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_uminus(void)
{
  __asm__(
   "fneg f1, f1\n"
  );
}
void nseel_asm_uminus_end(void) {}


//---------------------------------------------------------------------------------------------------------------
void nseel_asm_sign(void)
{
  __asm__(
    "li r9, 0\n"
    "stw r9, -4(r1)\n"
    "lis r9, 0xbf80\n" // -1 in float
    "lfs f2, -4(r1)\n"

    "fcmpu cr7, f1, f2\n"
    "blt- cr7, 0f\n"
      "ble- cr7, 1f\n"
        "  lis r9, 0x3f80\n" // 1 in float
    "0:\n"
    "  stw  r9, -4(r1)\n"
    "  lfs f1, -4(r1)\n"
    "1:\n"
    :: 
  );
}
void nseel_asm_sign_end(void) {}



//---------------------------------------------------------------------------------------------------------------
void nseel_asm_bnot(void)
{
  __asm__(
    "cmpwi cr0, r3, 0\n"
    "addis r3, 0, 0\n"
    "bne cr0, 0f\n"
    "addis r3, 0, 1\n"
    "0:\n"
  );
}
void nseel_asm_bnot_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_if(void)
{
  __asm__(
   "cmpwi cr0, r3, 0\n"
   "beq cr0, 0f\n"
   "  addis r6, 0, 0xdead\n"
   "  ori r6, r6, 0xbeef\n"
   "  mtctr r6\n"
   "  bctrl\n"
   "b 1f\n"
   "0:\n"
   "  addis r6, 0, 0xdead\n"
   "  ori r6, r6, 0xbeef\n"
   "  mtctr r6\n"
   "  bctrl\n"
   "1:\n"
  :: );
}
void nseel_asm_if_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_repeat(void)
{
  __asm__(
   "addis r6, 0, 0xdead\n"
   "ori r6, r6, 0xbeef\n"
   "addis r7, 0, ha16(%0)\n"
   "addi r7, r7, lo16(%0)\n"
   "fctiwz f1, f1\n"
   "stfd f1, 8(r16)\n"
   "lwz r5, 12(r16)\n" // r5 has count now
   "cmpwi cr0, r5, 0\n"
   "ble cr0, 1f\n"
   "cmpw cr0, r7, r5\n"
   "bge cr0, 0f\n"
   "mr r5, r7\n" // set r5 to max if we have to
"0:\n"
   "stw r5, -4(r1)\n"
   "stw r6, -8(r1)\n"
   "stwu r16, -12(r1)\n"

   "mtctr r6\n"
   "bctrl\n"

   "lwz r16, 0(r1)\n"
   "lwz r6, 4(r1)\n"
   "lwz r5, 8(r1)\n"
   "addi r1, r1, 12\n"
   "addi r5, r5, -1\n"

   "cmpwi cr0, r5, 0\n"
   "bgt cr0, 0b\n"
   "1:\n"
    ::"g" (NSEEL_LOOPFUNC_SUPPORT_MAXLEN)
  );
}
void nseel_asm_repeat_end(void) {}

void nseel_asm_repeatwhile(void)
{
  __asm__(
   "addis r6, 0, 0xdead\n"
   "ori r6, r6, 0xbeef\n"
   "addis r5, 0, ha16(%0)\n"
   "addi r5, r5, lo16(%0)\n"
"0:\n"
   "stw r5, -4(r1)\n"
   "stw r6, -8(r1)\n"
   "stwu r16, -12(r1)\n"

   "mtctr r6\n"
   "bctrl\n"

   "lwz r16, 0(r1)\n"
   "lwz r6, 4(r1)\n"
   "lwz r5, 8(r1)\n"
   "addi r1, r1, 12\n"
   "addi r5, r5, -1\n"

   "cmpwi cr7, r3, 0\n"
   "beq cr7, 1f\n"

   "cmpwi cr0, r5, 0\n"
   "bgt cr0, 0b\n"
   "1:\n"
    ::"g" (NSEEL_LOOPFUNC_SUPPORT_MAXLEN)
  );
}
void nseel_asm_repeatwhile_end(void) {}


void nseel_asm_band(void)
{
  __asm__(
   "cmpwi cr7, r3, 0\n"
   "beq cr7, 0f\n"
   "  addis r6, 0, 0xdead\n"
   "  ori r6, r6, 0xbeef\n"
   "  mtctr r6\n"
   "  bctrl\n"
   "0:\n"
  :: );
}
void nseel_asm_band_end(void) {}

void nseel_asm_bor(void)
{
  __asm__(
   "cmpwi cr7, r3, 0\n"
   "bne cr7, 0f\n"
   "  addis r6, 0, 0xdead\n"
   "  ori r6, r6, 0xbeef\n"
   "  mtctr r6\n"
   "  bctrl\n"
   "0:\n"
  :: );
}
void nseel_asm_bor_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_equal(void)
{
  __asm__(
    "lfd f2, 0(r14)\n"
    "fsub f1, f1, f2\n"
    "fabs f1, f1\n"
    "fcmpu cr7, f1, f14\n"
    "addis r3, 0, 0\n"
    "bge cr7, 0f\n"
    "addis r3, 0, 1\n"
    "0:\n"
    :: 
  );
}
void nseel_asm_equal_end(void) {}
//
//---------------------------------------------------------------------------------------------------------------
void nseel_asm_notequal(void)
{
  __asm__(
    "lfd f2, 0(r14)\n"
    "fsub f1, f1, f2\n"
    "fabs f1, f1\n"
    "fcmpu cr7, f1, f14\n"
    "addis r3, 0, 0\n"
    "blt cr7, 0f\n"
    "  addis r3, 0, 1\n"
    "0:\n"
    :: 
  );
}
void nseel_asm_notequal_end(void) {}


//---------------------------------------------------------------------------------------------------------------
void nseel_asm_below(void)
{
  __asm__(
    "lfd f2, 0(r14)\n"
    "fcmpu cr7, f1, f2\n"
    "addis r3, 0, 0\n"
    "ble cr7, 0f\n"
    "addis r3, 0, 1\n"
    "0:\n"
    ::
  );
}
void nseel_asm_below_end(void) {}

//---------------------------------------------------------------------------------------------------------------
void nseel_asm_beloweq(void)
{
  __asm__(
    "lfd f2, 0(r14)\n"
    "fcmpu cr7, f1, f2\n"
    "addis r3, 0, 0\n"
    "blt cr7, 0f\n"
    "  addis r3, 0, 1\n"
    "0:\n"
    ::
  );
}
void nseel_asm_beloweq_end(void) {}


//---------------------------------------------------------------------------------------------------------------
void nseel_asm_above(void)
{
  __asm__(
    "lfd f2, 0(r14)\n"
    "fcmpu cr7, f1, f2\n"
    "addis r3, 0, 0\n"
    "bge cr7, 0f\n"
    "addis r3, 0, 1\n"
    "0:\n"
    ::
  );
}
void nseel_asm_above_end(void) {}

void nseel_asm_aboveeq(void)
{
  __asm__(
    "lfd f2, 0(r14)\n"
    "fcmpu cr7, f1, f2\n"
    "addis r3, 0, 0\n"
    "bgt cr7, 0f\n"
    "addis r3, 0, 1\n"
    "0:\n"
    ::
  );
}
void nseel_asm_aboveeq_end(void) {}



void nseel_asm_min(void)
{
  __asm__(
    "lfd f1, 0(r3)\n"
    "lfd f2, 0(r14)\n"
    "fcmpu cr7, f2, f1\n"
    "bgt cr7, 0f\n"
    "mr r3, r14\n"
    "0:\n"
  );
}
void nseel_asm_min_end(void) {}

void nseel_asm_max(void)
{
  __asm__(
    "lfd f1, 0(r3)\n"
    "lfd f2, 0(r14)\n"
    "fcmpu cr7, f2, f1\n"
    "blt cr7, 0f\n"
    "mr r3, r14\n"
    "0:\n"
  );
}

void nseel_asm_max_end(void) {}


void nseel_asm_min_fp(void)
{
  __asm__(
    "lfd f2, 0(r14)\n"
    "fcmpu cr7, f2, f1\n"
    "bgt cr7, 0f\n"
    "fmr f1, f2\n"
    "0:\n"
  );
}
void nseel_asm_min_fp_end(void) {}

void nseel_asm_max_fp(void)
{
  __asm__(
    "lfd f2, 0(r14)\n"
    "fcmpu cr7, f2, f1\n"
    "blt cr7, 0f\n"
    "fmr f1, f2\n"
    "0:\n"
  );
}

void nseel_asm_max_fp_end(void) {}






void _asm_generic3parm(void)
{
  __asm__(
   "mr r6, r3\n"
   "addis r3, 0, 0xdead\n"
   "ori r3, r3, 0xbeef\n"
   "addis r7, 0, 0xdead\n"
   "ori r7, r7, 0xbeef\n"
   "mr r4, r15\n"
   "mr r5, r14\n"
   "mtctr r7\n"
   "subi r1, r1, 64\n"
   "bctrl\n"
   "addi r1, r1, 64\n"
  ::
 ); 
}
void _asm_generic3parm_end(void) {}

void _asm_generic3parm_retd(void)
{
  __asm__(
   "mr r6, r3\n"
   "addis r3, 0, 0xdead\n"
   "ori r3, r3, 0xbeef\n"
   "addis r7, 0, 0xdead\n"
   "ori r7, r7, 0xbeef\n"
   "mr r4, r15\n"
   "mr r5, r14\n"
   "mtctr r7\n"
   "subi r1, r1, 64\n"
   "bctrl\n"
   "addi r1, r1, 64\n"
  ::
 ); 
}
void _asm_generic3parm_retd_end(void) {}


void _asm_generic2parm(void) // this prob neds to be fixed for ppc
{
  __asm__(
   "mr r5, r3\n"
   "addis r3, 0, 0xdead\n"
   "ori r3, r3, 0xbeef\n"
   "addis r7, 0, 0xdead\n"
   "ori r7, r7, 0xbeef\n"
   "mr r4, r14\n"
   "mtctr r7\n"
   "subi r1, r1, 64\n"
   "bctrl\n"
   "addi r1, r1, 64\n"
  ::
 ); 
}
void _asm_generic2parm_end(void) {}


void _asm_generic2parm_retd(void)
{
  __asm__(
   "mr r5, r3\n"
   "addis r3, 0, 0xdead\n"
   "ori r3, r3, 0xbeef\n"
   "addis r7, 0, 0xdead\n"
   "ori r7, r7, 0xbeef\n"
   "mr r4, r14\n"
   "mtctr r7\n"
   "subi r1, r1, 64\n"
   "bctrl\n"
   "addi r1, r1, 64\n"
  ::
 ); 
}
void _asm_generic2parm_retd_end(void) {}

void _asm_generic1parm(void) // this prob neds to be fixed for ppc
{
  __asm__(
   "mr r4, r3\n"
   "addis r3, 0, 0xdead\n"
   "ori r3, r3, 0xbeef\n"
   "addis r7, 0, 0xdead\n"
   "ori r7, r7, 0xbeef\n"
   "mtctr r7\n"
   "subi r1, r1, 64\n"
   "bctrl\n"
   "addi r1, r1, 64\n"
  ::
 ); 
}
void _asm_generic1parm_end(void) {}



void _asm_generic1parm_retd(void)
{
  __asm__(
   "mr r4, r3\n"
   "addis r3, 0, 0xdead\n"
   "ori r3, r3, 0xbeef\n"
   "addis r7, 0, 0xdead\n"
   "ori r7, r7, 0xbeef\n"
   "mtctr r7\n"
   "subi r1, r1, 64\n"
   "bctrl\n"
   "addi r1, r1, 64\n"
  ::
 ); 
}
void _asm_generic1parm_retd_end(void) {}




void _asm_megabuf(void)
{
  __asm__(
   "lfd f2, -8(r13)\n"
   "mr r3, r13\n"

   "fadd f1, f2, f1\n"

   // f1 has (float) index of array, r3 has EEL_F **
   "fctiwz f1, f1\n"
   "stfd f1, 8(r16)\n"
   "lwz r4, 12(r16)\n" // r4 is index of array

   "andis. r15, r4, 0xFF80\n" // check to see if it has any bits in 0xFF800000, which is 0xFFFFFFFF - (NSEEL_RAM_BLOCKS*NSEEL_RAM_ITEMSPERBLOCK - 1)
   "bne cr0, 1f\n" // out of range, jump to error

   // shr 14 (16 for NSEEL_RAM_ITEMSPERBLOCK, minus two for pointer size), which is rotate 18
   // mask 7 bits (NSEEL_RAM_BLOCKS), but leave two empty bits (pointer size)
   "rlwinm r15, r4, 18, 23, 29\n"
   "lwzx r15, r3, r15\n" // r15 = (r3+r15)
   "cmpi cr0, r15, 0\n"
   "beq cr0, 1f\n"

     // good news: we can do a direct addr return
     // bad news: more rlwinm ugliness!
     // shift left by 3 (sizeof(EEL_F)), mask off lower 3 bits, only allow 16 bits (NSEEL_RAM_ITEMSPERBLOCK) through
     "rlwinm r3, r4, 3, 13, 28\n" 

     // add offset of loaded block
     "add r3, r3, r15\n"
   // done, jump to end!
   "b 0f\n"

   "1:\n"
   // set up function call
     "addis r7, 0, 0xdead\n"
     "ori r7, r7, 0xbeef\n"
     "mtctr r7\n"
     "subi r1, r1, 64\n"
     "bctrl\n"
     "addi r1, r1, 64\n"
   "0:\n"
  ::
 ); 
}

void _asm_megabuf_end(void) {}

void _asm_gmegabuf(void)
{
  __asm__(
   "fadd f1, f14, f1\n"
   "addis r3, 0, 0xdead\n" // set up context pointer
   "ori r3, r3, 0xbeef\n"

   "fctiwz f1, f1\n"
   "subi r1, r1, 64\n"

   "addis r7, 0, 0xdead\n"
   "ori r7, r7, 0xbeef\n"

   "stfd f1, 8(r1)\n"
   "mtctr r7\n"

   "lwz r4, 12(r1)\n"

   "bctrl\n"
   "addi r1, r1, 64\n"
  ::
 ); 
}

void _asm_gmegabuf_end(void) {}

void nseel_asm_fcall(void)
{
  __asm__(
   "addis r6, 0, 0xdead\n"
   "ori r6, r6, 0xbeef\n"
   "mtctr r6\n"
   "bctrl\n"
  );
}
void nseel_asm_fcall_end(void) {}



void nseel_asm_stack_push(void)
{
  __asm__(

   "addis r6, 0, 0xdead\n"
   "ori r6, r6, 0xbeef\n" // r6 is stack

   "lfd f1, 0(r3)\n" // f1 is value to copy to stack
   "lwz r3, 0(r6)\n"

   "addis r14, 0, 0xdead\n"
   "ori r14, r14, 0xbeef\n" 
   "addi r3, r3, 0x8\n"

   "and r3, r3, r14\n"

   "addis r14, 0, 0xdead\n"
   "ori r14, r14, 0xbeef\n" 
   "or r3, r3, r14\n"

   "stfd f1, 0(r3)\n" // copy parameter to stack

   "stw r3, 0(r6)\n" // update stack state
  );
}
void nseel_asm_stack_push_end(void) {}

void nseel_asm_stack_pop(void)
{
  __asm__(
   "addis r6, 0, 0xdead\n"
   "ori r6, r6, 0xbeef\n" // r6 is stack
   "lwz r15, 0(r6)\n" // return the old stack pointer

   "lfd f1, 0(r15)\n"
   "subi r15, r15, 0x8\n"

   "addis r14, 0, 0xdead\n"
   "ori r14, r14, 0xbeef\n" 
   "and r15, r15, r14\n"

   "addis r14, 0, 0xdead\n"
   "ori r14, r14, 0xbeef\n" 
   "or r15, r15, r14\n"
   "stw r15, 0(r6)\n"

   "stfd f1, 0(r3)\n"
  );
}
void nseel_asm_stack_pop_end(void) {}



void nseel_asm_stack_pop_fast(void)
{
  __asm__(
   "addis r6, 0, 0xdead\n"
   "ori r6, r6, 0xbeef\n" // r6 is stack
   "lwz r3, 0(r6)\n" // return the old stack pointer

   "mr r15, r3\n"  // update stack pointer
   "subi r15, r15, 0x8\n"

   "addis r14, 0, 0xdead\n"
   "ori r14, r14, 0xbeef\n" 
   "and r15, r15, r14\n"

   "addis r14, 0, 0xdead\n"
   "ori r14, r14, 0xbeef\n" 
   "or r15, r15, r14\n"
   "stw r15, 0(r6)\n"
  );
}
void nseel_asm_stack_pop_fast_end(void) {}

void nseel_asm_stack_peek(void)
{
  __asm__(
    "fctiwz f1, f1\n"
    "stfd f1, 0(r16)\n"

    "addis r6, 0, 0xdead\n"
    "ori r6, r6, 0xbeef\n" // r6 is stack

    "lwz r14, 4(r16)\n"
    "rlwinm r14, r14,  3, 0, 28\n" // slwi r14, r14, 3 -- 3 is log2(sizeof(EEL_F)) -- 28 represents 31-3
    "lwz r3, 0(r6)\n" // return the old stack pointer

    "sub r3, r3, r14\n"

    "addis r14, 0, 0xdead\n"
    "ori r14, r14, 0xbeef\n" 
    "and r3, r3, r14\n"

    "addis r14, 0, 0xdead\n"
    "ori r14, r14, 0xbeef\n" 
    "or r3, r3, r14\n"
  );
}
void nseel_asm_stack_peek_end(void) {}


void nseel_asm_stack_peek_top(void)
{
  __asm__(
    "addis r6, 0, 0xdead\n"
    "ori r6, r6, 0xbeef\n" // r6 is stack
    "lwz r3, 0(r6)\n" // return the old stack pointer
  );
}
void nseel_asm_stack_peek_top_end(void) {}


void nseel_asm_stack_peek_int(void)
{
  __asm__(
    "addis r6, 0, 0xdead\n"
    "ori r6, r6, 0xbeef\n" // r6 is stack
    "lwz r3, 0(r6)\n" // return the old stack pointer

    "addis r14, 0, 0xdead\n" // add manual offset
    "ori r14, r14, 0xbeef\n" 
    "sub r3, r3, r14\n"

    "addis r14, 0, 0xdead\n"
    "ori r14, r14, 0xbeef\n" 
    "and r3, r3, r14\n"

    "addis r14, 0, 0xdead\n"
    "ori r14, r14, 0xbeef\n" 
    "or r3, r3, r14\n"
  );
}
void nseel_asm_stack_peek_int_end(void) {}

void nseel_asm_stack_exch(void)
{
  __asm__(
    "addis r6, 0, 0xdead\n"
    "ori r6, r6, 0xbeef\n" // r6 is stack
    "lfd f1, 0(r3)\n"
    "lwz r14, 0(r6)\n" 
    "lfd f2, 0(r14)\n"

    "stfd f1, 0(r14)\n"
    "stfd f2, 0(r3)\n"
  );
}
void nseel_asm_stack_exch_end(void) {}


void nseel_asm_booltofp(void)
{
  __asm__(
    "cmpwi cr7, r3, 0\n"
    "addis r3, 0, 0xdead\n"
    "ori r3, r3, 0xbeef\n"
    "bne cr7, 0f\n"
      "addis r3, 0, 0xdead\n"
      "ori r3, r3, 0xbeef\n"
    "0:\n"
    "lfd f1, 0(r3)\n"
  );
}
void nseel_asm_booltofp_end(void){ }

void nseel_asm_fptobool(void)
{
  __asm__(
    "fabs f1, f1\n"
    "fcmpu cr7, f1, f14\n"
    "addis r3, 0, 1\n"
    "bge cr7, 0f\n"
    "  addis r3, 0, 0\n"
    "0:\n"
    :: 
          );
}
void nseel_asm_fptobool_end(void){ }

