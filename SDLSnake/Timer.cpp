#include "Timer.h"



Timer::Timer() :
	m_startTicks(0),
	m_pauseTicks(0),
	m_isPaused(false),
	m_isStarted(false) {}


Timer::~Timer() {}


void Timer::start() {
	// Start the timer
	m_isStarted = true;
	// Unpause the timer
	m_isPaused = false;
	// Get the current time clock
	m_startTicks = SDL_GetTicks();
	m_pauseTicks = 0;
}


void Timer::stop() {
	// Stop the timer
	m_isStarted = false;
	// Unpause the timer
	m_isPaused = false;
	// Clear tick variables
	m_startTicks = 0;
	m_pauseTicks = 0;
}


void Timer::pause() {
	// If the timer is running and isn't paused
	if (m_isStarted && !m_isPaused) {
		// Pause the timer
		m_isPaused = true;
		// Calculate the paused ticks
		m_pauseTicks = SDL_GetTicks() - m_startTicks;
		m_startTicks = 0;
	}
}


void Timer::unpause() {
	// If the timer is running and isn't paused
	if (m_isStarted && m_isPaused) {
		// Unpause the timer
		m_isPaused = false;
		// Reset the starting ticks
		m_startTicks = SDL_GetTicks() - m_pauseTicks;
		m_pauseTicks = 0;
	}
}


uint32_t Timer::getTicks() const {
	// If the timer is not running
	if (!m_isStarted) {
		return 0;
	}

	// If the timer is paused
	if (m_isPaused) {
		// Return the number of ticks when the timer is paused
		return m_pauseTicks;
	} else {
		// Return difference between current time and start time
		return SDL_GetTicks() - m_startTicks;
	}

	return 0;
}


bool Timer::isPaused() const {
	return m_isPaused;
}


bool Timer::isStarted() const {
	return m_isStarted;
}
