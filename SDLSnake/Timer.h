#pragma once
#ifndef _TIMER_H
#define _TIMER_H
#include <SDL.h>

class Timer {
public:
	// Initialize members
	Timer();

	// Deallocate memory
	~Timer();

	// Various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	// Get the timer data
	uint32_t getTicks() const;

	// Check the status of the timer
	bool isPaused() const;
	bool isStarted() const;

private:
	// The clock time when timer starts
	uint32_t m_startTicks;

	// The ticks stored when the timer was paused
	uint32_t m_pauseTicks;

	// The timer status
	bool m_isPaused;
	bool m_isStarted;

};

#endif // !_TIMER_H
