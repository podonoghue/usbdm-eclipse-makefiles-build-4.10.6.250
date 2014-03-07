#include "derivative.h"
#include "Freedom.h"
#include "utilities.h"

#define LED_GREEN_MASK        (1<<LED_GREEN_NUM)
#define LED_GREEN_PCR         PCR(LED_GREEN_PORT,LED_GREEN_NUM)
#define LED_GREEN_PDOR        PDOR(LED_GREEN_PORT)
#define LED_GREEN_PSOR        PSOR(LED_GREEN_PORT)  // Data set
#define LED_GREEN_PCOR        PCOR(LED_GREEN_PORT)  // Data clear
#define LED_GREEN_PTOR        PTOR(LED_GREEN_PORT)  // Data toggle
#define LED_GREEN_PDIR        PDIR(LED_GREEN_PORT)  // Data input
#define LED_GREEN_PDDR        PDDR(LED_GREEN_PORT)  // Data direction

#define LED_RED_MASK          (1<<LED_RED_NUM)
#define LED_RED_PCR           PCR(LED_RED_PORT,LED_RED_NUM)
#define LED_RED_PDOR          PDOR(LED_RED_PORT)
#define LED_RED_PSOR          PSOR(LED_RED_PORT)  // Data set
#define LED_RED_PCOR          PCOR(LED_RED_PORT)  // Data clear
#define LED_RED_PTOR          PTOR(LED_RED_PORT)  // Data toggle
#define LED_RED_PDIR          PDIR(LED_RED_PORT)  // Data input
#define LED_RED_PDDR          PDDR(LED_RED_PORT)  // Data direction

#define LED_BLUE_MASK         (1<<LED_BLUE_NUM)
#define LED_BLUE_PCR          PCR(LED_BLUE_PORT,LED_BLUE_NUM)
#define LED_BLUE_PDOR         PDOR(LED_BLUE_PORT)
#define LED_BLUE_PSOR         PSOR(LED_BLUE_PORT)  // Data set
#define LED_BLUE_PCOR         PCOR(LED_BLUE_PORT)  // Data clear
#define LED_BLUE_PTOR         PTOR(LED_BLUE_PORT)  // Data toggle
#define LED_BLUE_PDIR         PDIR(LED_BLUE_PORT)  // Data input
#define LED_BLUE_PDDR         PDDR(LED_BLUE_PORT)  // Data direction

#define LED_ORANGE_MASK       (1<<LED_ORANGE_NUM)
#define LED_ORANGE_PCR        PCR(LED_ORANGE_PORT,LED_ORANGE_NUM)
#define LED_ORANGE_PDOR       PDOR(LED_ORANGE_PORT)
#define LED_ORANGE_PSOR       PSOR(LED_ORANGE_PORT)  // Data set
#define LED_ORANGE_PCOR       PCOR(LED_ORANGE_PORT)  // Data clear
#define LED_ORANGE_PTOR       PTOR(LED_ORANGE_PORT)  // Data toggle
#define LED_ORANGE_PDIR       PDIR(LED_ORANGE_PORT)  // Data input
#define LED_ORANGE_PDDR       PDDR(LED_ORANGE_PORT)  // Data direction

void greenLedOn(void) {
   LED_GREEN_PCOR = LED_GREEN_MASK;
}
void greenLedOff(void) {
   LED_GREEN_PSOR = LED_GREEN_MASK;
}
void greenLedToggle(void) {
   LED_GREEN_PTOR = LED_GREEN_MASK;
}
void redLedOn(void) {
   LED_RED_PCOR = LED_RED_MASK;
}
void redLedOff(void) {
   LED_RED_PSOR = LED_RED_MASK;
}
void redLedToggle(void) {
   LED_RED_PTOR = LED_RED_MASK;
}
#ifdef LED_BLUE_PORT
void blueLedOn(void) {
   LED_BLUE_PCOR = LED_BLUE_MASK;
}
void blueLedOff(void) {
   LED_BLUE_PSOR = LED_BLUE_MASK;
}
void blueLedToggle(void) {
   LED_BLUE_PTOR = LED_BLUE_MASK;
}
#endif
#ifdef LED_ORANGE_PORT
void orangeLedOn(void) {
   LED_ORANGE_PCOR = LED_ORANGE_MASK;
}
void orangeLedOff(void) {
   LED_ORANGE_PSOR = LED_ORANGE_MASK;
}
void orangeLedToggle(void) {
   LED_ORANGE_PTOR = LED_ORANGE_MASK;
}
#endif

#define CLOCK_MASK(port) CONCAT4_(SIM_SCGC5,_PORT,port,_MASK)

void led_initialise(void) {
#ifdef LED_GREEN_PORT
   SIM_SCGC5 |=  CLOCK_MASK(LED_GREEN_PORT);
   greenLedOff();
   LED_GREEN_PDDR  |= LED_GREEN_MASK;
   LED_GREEN_PCR    = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK;
#endif
#ifdef LED_RED_PORT
   SIM_SCGC5 |=  CLOCK_MASK(LED_RED_PORT);
   redLedOff();
   LED_RED_PDDR    |= LED_RED_MASK;
   LED_RED_PCR      = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK;
#endif
#ifdef LED_BLUE_PORT
   SIM_SCGC5 |=  CLOCK_MASK(LED_BLUE_PORT);
   blueLedOff();
   LED_BLUE_PDDR   |= LED_BLUE_MASK;
   LED_BLUE_PCR     = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK;
#endif
#ifdef LED_ORANGE_PORT
   SIM_SCGC5 |=  CLOCK_MASK(LED_ORANGE_PORT);
   orangeLedOff();
   LED_ORANGE_PDDR |= LED_ORANGE_MASK;
   LED_ORANGE_PCR   = PORT_PCR_MUX(1)|PORT_PCR_DSE_MASK;
#endif
}
