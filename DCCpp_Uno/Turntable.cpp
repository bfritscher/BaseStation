int internalPosition = 0; // 0-48
int direction = 1; // -1 || 1
int currentTarget = 0; // 0-48

// if in EPROM?
loadInternalPostion();


void moveTo(int target) {
    currentTarget = target;
    setSpeed(SLOW);
    switchOn // test if short enough for 1
    move();
}

void move() {
    int delta = currentTarget - internalPosition;
    // calculate shortest direction
    if (delta > 24 ) {
        delta = delta - 48;
    }
    if (delta < -24 ) {
        delta = delta + 48;
    }
    direction = delta >= 0 ? 1 : -1;
    // speed based on distance
    if (delta == 0) {
        switchOff()
        timeout(setSpeed(OFF))
    } else if (delta == 99) {
        //lock
        resetInternalPosition
        setSpeed(OFF);
    } else if (delta == 1) {
        setSpeed(SLOW);
    } else if (delta >= 4) {
        setSpeed(FAST);
    } else {
        setSpeed(MEDIUM);
    }
}

// Voltages
int OFF = 0;
int SLOW = 12;
int MEDIUM = 14;
int FAST = 18;

void setSpeed(speed) {
    //TODO set motorshield to speed voltage
}

//TODO thread
void feedbackLoop() {
    //lock?
    internalPosition += direction;
    saveInternalPosition();
    move();
}
