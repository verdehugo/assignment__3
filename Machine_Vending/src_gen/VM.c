/** Generated by itemis CREATE code generator. */


#include "../src/sc_types.h"

#include "VM.h"
#include "VM_required.h"

/*! \file
Implementation of the state machine 'VM'
*/

#ifndef SC_UNUSED
#define SC_UNUSED(P) (void)(P)
#endif

/* prototypes of all internal functions */
static void enact_main_region_IDLE(VM* handle);
static void enact_main_region_product_browse(VM* handle);
static void enact_main_region_product_dispense(VM* handle);
static void enact_main_region_return_credit(VM* handle);
static void enseq_main_region_IDLE_default(VM* handle);
static void enseq_main_region_product_browse_default(VM* handle);
static void enseq_main_region_product_dispense_default(VM* handle);
static void enseq_main_region_return_credit_default(VM* handle);
static void enseq_main_region_default(VM* handle);
static void exseq_main_region_IDLE(VM* handle);
static void exseq_main_region_product_browse(VM* handle);
static void exseq_main_region_product_dispense(VM* handle);
static void exseq_main_region_return_credit(VM* handle);
static void exseq_main_region(VM* handle);
static void react_main_region__entry_Default(VM* handle);

/*! State machine reactions. */
static sc_integer react(VM* handle, const sc_integer transitioned_before);

/*! The reactions of state IDLE. */
static sc_integer main_region_IDLE_react(VM* handle, const sc_integer transitioned_before);

/*! The reactions of state product browse. */
static sc_integer main_region_product_browse_react(VM* handle, const sc_integer transitioned_before);

/*! The reactions of state product dispense. */
static sc_integer main_region_product_dispense_react(VM* handle, const sc_integer transitioned_before);

/*! The reactions of state return credit. */
static sc_integer main_region_return_credit_react(VM* handle, const sc_integer transitioned_before);


static void clear_in_events(VM* handle);

static void micro_step(VM* handle);

/*! Performs a 'run to completion' step. */
static void run_cycle(VM* handle);




static void vM_internal_set_credit(VM* handle, sc_integer value)
;
static void vM_internal_set_product(VM* handle, sc_integer value)
;
static void vM_internal_set_price(VM* handle, sc_integer value)
;


static void vm_eventqueue_init(vm_eventqueue * eq, vm_event *buffer, sc_integer capacity);
static sc_integer vm_eventqueue_size(vm_eventqueue * eq);
static void vm_event_init(vm_event * ev, VMEventID name);
static vm_event vm_eventqueue_pop(vm_eventqueue * eq);
static sc_boolean vm_eventqueue_push(vm_eventqueue * eq, vm_event ev);
static void vM_add_event_to_queue(vm_eventqueue * eq, VMEventID name);
static sc_boolean vM_dispatch_event(VM* handle, const vm_event * event);
static vm_event vM_get_next_event(VM* handle);
static sc_boolean vM_dispatch_next_event(VM* handle);


void vM_init(VM* handle)
{
	sc_integer i;
	
	for (i = 0; i < VM_MAX_ORTHOGONAL_STATES; ++i)
	{
		handle->stateConfVector[i] = VM_last_state;
	}
	
				
	clear_in_events(handle);
	
	
	/* Default init sequence for statechart VM */
	vM_internal_set_credit(handle, 0);
	vM_internal_set_product(handle, 0);
	vM_internal_set_price(handle, 0);
	
	handle->isExecuting = bool_false;
	vm_eventqueue_init(&handle->in_event_queue, handle->in_buffer, VM_IN_EVENTQUEUE_BUFFERSIZE);
}

void vM_enter(VM* handle)
{
	/* Activates the state machine. */
	if (handle->isExecuting == bool_true)
	{ 
		return;
	} 
	handle->isExecuting = bool_true;
	/* Default enter sequence for statechart VM */
	enseq_main_region_default(handle);
	handle->isExecuting = bool_false;
}

void vM_exit(VM* handle)
{
	/* Deactivates the state machine. */
	if (handle->isExecuting == bool_true)
	{ 
		return;
	} 
	handle->isExecuting = bool_true;
	/* Default exit sequence for statechart VM */
	exseq_main_region(handle);
	handle->isExecuting = bool_false;
}

/*!
Can be used by the client code to trigger a run to completion step without raising an event.
*/
void vM_trigger_without_event(VM* handle) {
	run_cycle(handle);
}


sc_boolean vM_is_active(const VM* handle)
{
	sc_boolean result = bool_false;
	sc_integer i;
	
	for(i = 0; i < VM_MAX_ORTHOGONAL_STATES; i++)
	{
		result = result || handle->stateConfVector[i] != VM_last_state;
	}
	
	return result;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean vM_is_final(const VM* handle)
{
	SC_UNUSED(handle);
	return bool_false;
}

sc_boolean vM_is_state_active(const VM* handle, VMStates state)
{
	sc_boolean result = bool_false;
	switch (state)
	{
		case VM_main_region_IDLE :
			result = (sc_boolean) (handle->stateConfVector[SCVI_VM_MAIN_REGION_IDLE] == VM_main_region_IDLE
			);
				break;
		case VM_main_region_product_browse :
			result = (sc_boolean) (handle->stateConfVector[SCVI_VM_MAIN_REGION_PRODUCT_BROWSE] == VM_main_region_product_browse
			);
				break;
		case VM_main_region_product_dispense :
			result = (sc_boolean) (handle->stateConfVector[SCVI_VM_MAIN_REGION_PRODUCT_DISPENSE] == VM_main_region_product_dispense
			);
				break;
		case VM_main_region_return_credit :
			result = (sc_boolean) (handle->stateConfVector[SCVI_VM_MAIN_REGION_RETURN_CREDIT] == VM_main_region_return_credit
			);
				break;
			default:
				result = bool_false;
				break;
		}
		return result;
	}

static void clear_in_events(VM* handle)
{
	handle->ifaceBut.coin1_raised = bool_false;
	handle->ifaceBut.coin2_raised = bool_false;
	handle->ifaceBut.browse_raised = bool_false;
	handle->ifaceBut.enter_raised = bool_false;
}

static void micro_step(VM* handle)
{
	switch(handle->stateConfVector[ 0 ])
	{
		case VM_main_region_IDLE :
		{
			main_region_IDLE_react(handle,-1);
			break;
		}
		case VM_main_region_product_browse :
		{
			main_region_product_browse_react(handle,-1);
			break;
		}
		case VM_main_region_product_dispense :
		{
			main_region_product_dispense_react(handle,-1);
			break;
		}
		case VM_main_region_return_credit :
		{
			main_region_return_credit_react(handle,-1);
			break;
		}
		default: 
			/* do nothing */
			break;
	}
}

static void run_cycle(VM* handle)
{
	/* Performs a 'run to completion' step. */
	if (handle->isExecuting == bool_true)
	{ 
		return;
	} 
	handle->isExecuting = bool_true;
	vM_dispatch_next_event(handle);
	do
	{ 
		micro_step(handle);
		clear_in_events(handle);
	} while (vM_dispatch_next_event(handle) == bool_true);
	handle->isExecuting = bool_false;
}


void vM_but_raise_coin1(VM* handle)
{
	vM_add_event_to_queue(&(handle->in_event_queue), VM_but_coin1);
	run_cycle(handle);
}

void vM_but_raise_coin2(VM* handle)
{
	vM_add_event_to_queue(&(handle->in_event_queue), VM_but_coin2);
	run_cycle(handle);
}

void vM_but_raise_browse(VM* handle)
{
	vM_add_event_to_queue(&(handle->in_event_queue), VM_but_browse);
	run_cycle(handle);
}

void vM_but_raise_enter(VM* handle)
{
	vM_add_event_to_queue(&(handle->in_event_queue), VM_but_enter);
	run_cycle(handle);
}






static void vM_internal_set_credit(VM* handle, sc_integer value)
{
	handle->internal.credit = value;
}
static void vM_internal_set_product(VM* handle, sc_integer value)
{
	handle->internal.product = value;
}
static void vM_internal_set_price(VM* handle, sc_integer value)
{
	handle->internal.price = value;
}


/* implementations of all internal functions */

/* Entry action for state 'IDLE'. */
static void enact_main_region_IDLE(VM* handle)
{
	/* Entry action for state 'IDLE'. */
	vM_welcome_message(handle);
}

/* Entry action for state 'product browse'. */
static void enact_main_region_product_browse(VM* handle)
{
	/* Entry action for state 'product browse'. */
	if ((handle->internal.product) == (0))
	{ 
		vM_internal_set_price(handle, 0);
	} 
	if ((handle->internal.product) == (1))
	{ 
		vM_internal_set_price(handle, 1);
	} 
	if ((handle->internal.product) == (2))
	{ 
		vM_internal_set_price(handle, 2);
	} 
	if ((handle->internal.product) == (3))
	{ 
		vM_internal_set_price(handle, 3);
	} 
	if ((handle->internal.product) > (3))
	{ 
		vM_internal_set_product(handle, 0);
		vM_internal_set_price(handle, 0);
	} 
	vM_select_product(handle,handle->internal.product, handle->internal.credit);
}

/* Entry action for state 'product dispense'. */
static void enact_main_region_product_dispense(VM* handle)
{
	/* Entry action for state 'product dispense'. */
	vM_dispense_product(handle,handle->internal.product);
	vM_internal_set_credit(handle, handle->internal.credit - handle->internal.price);
}

/* Entry action for state 'return credit'. */
static void enact_main_region_return_credit(VM* handle)
{
	/* Entry action for state 'return credit'. */
	vM_return_credit(handle,handle->internal.credit);
}

/* 'default' enter sequence for state IDLE */
static void enseq_main_region_IDLE_default(VM* handle)
{
	/* 'default' enter sequence for state IDLE */
	enact_main_region_IDLE(handle);
	handle->stateConfVector[0] = VM_main_region_IDLE;
}

/* 'default' enter sequence for state product browse */
static void enseq_main_region_product_browse_default(VM* handle)
{
	/* 'default' enter sequence for state product browse */
	enact_main_region_product_browse(handle);
	handle->stateConfVector[0] = VM_main_region_product_browse;
}

/* 'default' enter sequence for state product dispense */
static void enseq_main_region_product_dispense_default(VM* handle)
{
	/* 'default' enter sequence for state product dispense */
	enact_main_region_product_dispense(handle);
	handle->stateConfVector[0] = VM_main_region_product_dispense;
}

/* 'default' enter sequence for state return credit */
static void enseq_main_region_return_credit_default(VM* handle)
{
	/* 'default' enter sequence for state return credit */
	enact_main_region_return_credit(handle);
	handle->stateConfVector[0] = VM_main_region_return_credit;
}

/* 'default' enter sequence for region main region */
static void enseq_main_region_default(VM* handle)
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default(handle);
}

/* Default exit sequence for state IDLE */
static void exseq_main_region_IDLE(VM* handle)
{
	/* Default exit sequence for state IDLE */
	handle->stateConfVector[0] = VM_last_state;
}

/* Default exit sequence for state product browse */
static void exseq_main_region_product_browse(VM* handle)
{
	/* Default exit sequence for state product browse */
	handle->stateConfVector[0] = VM_last_state;
}

/* Default exit sequence for state product dispense */
static void exseq_main_region_product_dispense(VM* handle)
{
	/* Default exit sequence for state product dispense */
	handle->stateConfVector[0] = VM_last_state;
}

/* Default exit sequence for state return credit */
static void exseq_main_region_return_credit(VM* handle)
{
	/* Default exit sequence for state return credit */
	handle->stateConfVector[0] = VM_last_state;
}

/* Default exit sequence for region main region */
static void exseq_main_region(VM* handle)
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of VM.main_region) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case VM_main_region_IDLE :
		{
			exseq_main_region_IDLE(handle);
			break;
		}
		case VM_main_region_product_browse :
		{
			exseq_main_region_product_browse(handle);
			break;
		}
		case VM_main_region_product_dispense :
		{
			exseq_main_region_product_dispense(handle);
			break;
		}
		case VM_main_region_return_credit :
		{
			exseq_main_region_return_credit(handle);
			break;
		}
		default: 
			/* do nothing */
			break;
	}
}

/* Default react sequence for initial entry  */
static void react_main_region__entry_Default(VM* handle)
{
	/* Default react sequence for initial entry  */
	vM_internal_set_credit(handle, 0);
	vM_internal_set_product(handle, 0);
	enseq_main_region_IDLE_default(handle);
}


static sc_integer react(VM* handle, const sc_integer transitioned_before)
{
	/* State machine reactions. */
	SC_UNUSED(handle);
	return transitioned_before;
}

static sc_integer main_region_IDLE_react(VM* handle, const sc_integer transitioned_before)
{
	/* The reactions of state IDLE. */
 			sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (handle->ifaceBut.coin1_raised == bool_true)
		{ 
			exseq_main_region_IDLE(handle);
			handle->internal.credit++;
			enseq_main_region_product_browse_default(handle);
			react(handle,0);
			transitioned_after = 0;
		}  else
		{
			if (handle->ifaceBut.coin2_raised == bool_true)
			{ 
				exseq_main_region_IDLE(handle);
				vM_internal_set_credit(handle, handle->internal.credit + 2);
				enseq_main_region_product_browse_default(handle);
				react(handle,0);
				transitioned_after = 0;
			}  else
			{
				if (handle->ifaceBut.browse_raised == bool_true)
				{ 
					exseq_main_region_IDLE(handle);
					enseq_main_region_product_browse_default(handle);
					react(handle,0);
					transitioned_after = 0;
				} 
			}
		}
	} 
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		transitioned_after = react(handle,transitioned_before);
	} 
	return transitioned_after;
}

static sc_integer main_region_product_browse_react(VM* handle, const sc_integer transitioned_before)
{
	/* The reactions of state product browse. */
 			sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (handle->ifaceBut.coin1_raised == bool_true)
		{ 
			exseq_main_region_product_browse(handle);
			handle->internal.credit++;
			enseq_main_region_product_browse_default(handle);
			react(handle,0);
			transitioned_after = 0;
		}  else
		{
			if (handle->ifaceBut.coin2_raised == bool_true)
			{ 
				exseq_main_region_product_browse(handle);
				vM_internal_set_credit(handle, handle->internal.credit + 2);
				enseq_main_region_product_browse_default(handle);
				react(handle,0);
				transitioned_after = 0;
			}  else
			{
				if (handle->ifaceBut.browse_raised == bool_true)
				{ 
					exseq_main_region_product_browse(handle);
					handle->internal.product++;
					enseq_main_region_product_browse_default(handle);
					react(handle,0);
					transitioned_after = 0;
				}  else
				{
					if (((handle->ifaceBut.enter_raised) == bool_true) && (((handle->internal.product) == (0)) == bool_true))
					{ 
						exseq_main_region_product_browse(handle);
						enseq_main_region_return_credit_default(handle);
						react(handle,0);
						transitioned_after = 0;
					}  else
					{
						if (((handle->ifaceBut.enter_raised) == bool_true) && (((handle->internal.credit) < (handle->internal.price)) == bool_true))
						{ 
							exseq_main_region_product_browse(handle);
							enseq_main_region_product_browse_default(handle);
							react(handle,0);
							transitioned_after = 0;
						}  else
						{
							if (((handle->ifaceBut.enter_raised) == bool_true) && (((handle->internal.credit) >= (handle->internal.price)) == bool_true))
							{ 
								exseq_main_region_product_browse(handle);
								enseq_main_region_product_dispense_default(handle);
								react(handle,0);
								transitioned_after = 0;
							} 
						}
					}
				}
			}
		}
	} 
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		transitioned_after = react(handle,transitioned_before);
	} 
	return transitioned_after;
}

static sc_integer main_region_product_dispense_react(VM* handle, const sc_integer transitioned_before)
{
	/* The reactions of state product dispense. */
 			sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (handle->ifaceBut.enter_raised == bool_true)
		{ 
			exseq_main_region_product_dispense(handle);
			enseq_main_region_return_credit_default(handle);
			react(handle,0);
			transitioned_after = 0;
		} 
	} 
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		transitioned_after = react(handle,transitioned_before);
	} 
	return transitioned_after;
}

static sc_integer main_region_return_credit_react(VM* handle, const sc_integer transitioned_before)
{
	/* The reactions of state return credit. */
 			sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (handle->ifaceBut.enter_raised == bool_true)
		{ 
			exseq_main_region_return_credit(handle);
			vM_internal_set_credit(handle, 0);
			vM_internal_set_product(handle, 0);
			vM_internal_set_price(handle, 0);
			enseq_main_region_IDLE_default(handle);
			react(handle,0);
			transitioned_after = 0;
		} 
	} 
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		transitioned_after = react(handle,transitioned_before);
	} 
	return transitioned_after;
}




static void vm_eventqueue_init(vm_eventqueue * eq, vm_event *buffer, sc_integer capacity)
{
	eq->events = buffer;
	eq->capacity = capacity;
	eq->push_index = 0;
	eq->pop_index = 0;
	eq->size = 0;
}

static sc_integer vm_eventqueue_size(vm_eventqueue * eq)
{
	return eq->size;
}

static vm_event vm_eventqueue_pop(vm_eventqueue * eq)
{
	vm_event event;
	if(vm_eventqueue_size(eq) <= 0) {
		vm_event_init(&event, VM_invalid_event);
	}
	else {
		event = eq->events[eq->pop_index];
		
		if(eq->pop_index < eq->capacity - 1) {
			eq->pop_index++;
		} 
		else {
			eq->pop_index = 0;
		}
		eq->size--;
	}
	return event;
}
static sc_boolean vm_eventqueue_push(vm_eventqueue * eq, vm_event ev)
{
	if(vm_eventqueue_size(eq) == eq->capacity) {
		return bool_false;
	}
	else {
		eq->events[eq->push_index] = ev;
		
		if(eq->push_index < eq->capacity - 1) {
			eq->push_index++;
		}
		else {
			eq->push_index = 0;
		}
		eq->size++;
		
		return bool_true;
	}
}
static void vm_event_init(vm_event * ev, VMEventID name)
{
	ev->name = name;
}

static void vM_add_event_to_queue(vm_eventqueue * eq, VMEventID name)
{
	vm_event event;
	vm_event_init(&event, name);
	vm_eventqueue_push(eq, event);
}

static sc_boolean vM_dispatch_event(VM* handle, const vm_event * event) {
	switch(event->name) {
		case VM_but_coin1:
		{
			handle->ifaceBut.coin1_raised = bool_true;
			return bool_true;
		}
		case VM_but_coin2:
		{
			handle->ifaceBut.coin2_raised = bool_true;
			return bool_true;
		}
		case VM_but_browse:
		{
			handle->ifaceBut.browse_raised = bool_true;
			return bool_true;
		}
		case VM_but_enter:
		{
			handle->ifaceBut.enter_raised = bool_true;
			return bool_true;
		}
		default:
			return bool_false;
	}
}

static vm_event vM_get_next_event(VM* handle)
{
	vm_event next_event;
	vm_event_init(&next_event, VM_invalid_event);
	if(vm_eventqueue_size(&(handle->in_event_queue)) > 0) {
		next_event = vm_eventqueue_pop(&(handle->in_event_queue));
	}
	return next_event;
}

static sc_boolean vM_dispatch_next_event(VM* handle)
{
	vm_event nextEvent;
	nextEvent = vM_get_next_event(handle);
	return vM_dispatch_event(handle, &nextEvent);
}
