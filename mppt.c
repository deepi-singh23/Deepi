/*
************************************************************
* NOTE: Automatically generated file. DO NOT MODIFY!
************************************************************
*
* File: mppt.c
*
* Code generated from model             : 'tidal'.
* Subsystem selected for code generation: 'mppt'.
*
* Schematic Editor version              : 2023.1 SP1
* C source code generated on            : 17-Jul-2023 @ 01:54:45 AM
*
*/

#include "mppt.h"

//@cmp.def.start
// custom defines
//@cmp.def.end

// Model entry point functions
void mppt_step(mppt_ModelData *p_m_Data) {
    mppt_ExtIn *ext_In = (mppt_ExtIn *) p_m_Data->p_extIn;
    mppt_ExtOut *ext_Out = (mppt_ExtOut *) p_m_Data->p_extOut;
    mppt_ModelSinks *m_Sinks = (mppt_ModelSinks *) p_m_Data->p_Sinks;
    mppt_ModelStates *m_States = (mppt_ModelStates *) p_m_Data->p_States;
    //////////////////////////////////////////////////////////////////////////
    // Local variables
    //////////////////////////////////////////////////////////////////////////
    //@cmp.var.start
    real_t _mppt_unit_delay1__out;
    real_t _mppt_unit_delay2__out;
    real_t _mppt_pv_power__out;
    real_t _mppt_sum2__out;
    real_t _mppt_sum1__out;
    real_t _mppt_p_o__Power;
    real_t _mppt_p_o__Voltage;
    real_t _mppt_p_o__out;
//@cmp.var.end
    //////////////////////////////////////////////////////////////////////////
    // Output block
    //////////////////////////////////////////////////////////////////////////
    //@cmp.out.block.start
    // Generated from the component: MPPT.Unit Delay1
    _mppt_unit_delay1__out = m_States->_mppt_unit_delay1__state;
    // Generated from the component: MPPT.Unit Delay2
    _mppt_unit_delay2__out = m_States->_mppt_unit_delay2__state;
    // Generated from the component: MPPT.PV power
    _mppt_pv_power__out = (ext_In->Idc * ext_In->Vdc);
    // Generated from the component: MPPT.Sum2
    _mppt_sum2__out = ext_In->Vdc - _mppt_unit_delay2__out;
    // Generated from the component: MPPT.Sum1
    _mppt_sum1__out = _mppt_pv_power__out - _mppt_unit_delay1__out;
    // Generated from the component: MPPT.P&O
    _mppt_p_o__Power = _mppt_sum1__out;
    _mppt_p_o__Voltage = _mppt_sum2__out;
    if (_mppt_p_o__Power == 0) {
        m_States->_mppt_p_o__step = 0;
    }
    else if (_mppt_p_o__Power > 0) {
        if (_mppt_p_o__Voltage > 0)m_States->_mppt_p_o__step = -1 * m_States->_mppt_p_o__delta_duty_cycle;
        else m_States->_mppt_p_o__step = m_States->_mppt_p_o__delta_duty_cycle;
    }
    else if (_mppt_p_o__Power < 0) {
        if (_mppt_p_o__Voltage > 0)m_States->_mppt_p_o__step = m_States->_mppt_p_o__delta_duty_cycle;
        else m_States->_mppt_p_o__step = -1 * m_States->_mppt_p_o__delta_duty_cycle;
    }
    m_States->_mppt_p_o__duty_cycle = m_States->_mppt_p_o__duty_cycle + m_States->_mppt_p_o__step;
    if (m_States->_mppt_p_o__duty_cycle < m_States->_mppt_p_o__min_val)m_States->_mppt_p_o__duty_cycle = m_States->_mppt_p_o__min_val;
    else if (m_States->_mppt_p_o__duty_cycle > m_States->_mppt_p_o__max_val)m_States->_mppt_p_o__duty_cycle = m_States->_mppt_p_o__max_val;
    _mppt_p_o__out = m_States->_mppt_p_o__duty_cycle;
///////////////
    // Update sinks
    ///////////////
    m_Sinks->_mppt_p_pv_in = _mppt_pv_power__out;
    m_Sinks->_mppt_reference_o_in = _mppt_p_o__out;
    m_Sinks->_mppt_reference_out_in = _mppt_p_o__out;
    ////////////////
    // Update output
    ////////////////
    ext_Out->reference = _mppt_p_o__out;
    //@cmp.out.block.end
    //////////////////////////////////////////////////////////////////////////
    // Update block
    //////////////////////////////////////////////////////////////////////////
    //@cmp.update.block.start
    // Generated from the component: MPPT.Unit Delay1
    m_States->_mppt_unit_delay1__state = _mppt_pv_power__out;
    // Generated from the component: MPPT.Unit Delay2
    m_States->_mppt_unit_delay2__state = ext_In->Vdc;
    // Generated from the component: MPPT.P&O
//@cmp.update.block.end
}

void mppt_init(mppt_ModelData *p_m_Data) {
    //@cmp.init.block.start
    mppt_ModelStates *m_States = (mppt_ModelStates *) p_m_Data->p_States;
    m_States->_mppt_unit_delay1__state = 0.0;
    m_States->_mppt_unit_delay2__state = 0.0;
    m_States->_mppt_p_o__duty_cycle = 0;
    m_States->_mppt_p_o__delta_duty_cycle = 0.0009;
    m_States->_mppt_p_o__max_val = 0.8;
    m_States->_mppt_p_o__min_val = 0.2;
    //@cmp.init.block.end
}
