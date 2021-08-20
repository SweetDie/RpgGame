#pragma once
#include"Defines.h"
#include"Constants.h"

template <typename T>
class Atribute
{
public:
	Atribute(T current, T max)
	{
		if (current >= 0 && max >= 0)
		{
			this->current = current;
			this->max = max;
		}
		else
		{
			this->current = 0;
			this->max = 0;
		}
	}
	void setCurrent(T current)
	{
		if (current > this->max)
		{
			this->current = this->max;
		}
		else
		{
			this->current = current;
		}
	}
	void setMax(T max)
	{
		if (max < 0)
		{
			this->max = 0;
		}
		else
		{
			this->max = max;
			if (this->current > this->max)
			{
				this->current = this->max;
			}
		}
	}
	void set(T current, T max)
	{
		if (current >= 0 && max >= 0)
		{
			this->max = max;
			if (current <= max)
			{
				this->current = current;
			}
			else
			{
				this->current = this->max;
			}
		}
	}
	void levelUp(T levelFactor)
	{
		if (levelFactor >= 1)
		{
			this->max *= levelFactor;
			this->current = this->max;
		}
	}
	T getCurrent() const
	{
		return current;
	}
	T getMax() const
	{
		return max;
	}

	//Operators
	// +
	Atribute<T>& operator+(const Atribute<T>& other)
	{
		Atribute<T> tmp(other.current + this->current, this->max + other.max);
		if (tmp.current > tmp.max)
		{
			tmp.current = tmp.max;
		}
		return tmp;
	}
	Atribute<T>& operator+(const T& value)
	{
		Atribute<T> tmp(value + this->current, this->max);
		if (tmp.current > tmp.max)
		{
			tmp.current = tmp.max;
		}
		return tmp;
	}
	// -
	Atribute<T>& operator-(const Atribute<T>& other)
	{
		Atribute<T> tmp(this->current - other.current, this->max - other.max);
		if (tmp.max < 0)
		{
			tmp.max = 0;
			tmp.current = tmp.max;
		}
		else if (tmp.current > tmp.max)
		{
			tmp.current = tmp.max;
		}
		else if (tmp.current < 0)
		{
			tmp.current = 0;
		}
		return tmp;
	}
	Atribute<T>& operator-(const T& value)
	{
		Atribute<T> tmp(this->current - value, this->max);
		if (tmp.current < 0)
		{
			tmp.current = 0;
		}
		else if (tmp.current > tmp.max)
		{
			tmp.current = tmp.max;
		}
		return tmp;
	}
	// =
	Atribute<T>& operator=(const Atribute<T>& other)
	{
		this->current = other.current;
		this->max = other.max;
		if (this->current > this->max)
		{
			this->current = this->max;
		}
		return *this;
	}
	Atribute<T>& operator=(const T& value)
	{
		this->current = value;
		if (this->current > this->max)
		{
			this->current = this->max;
		}
		return *this;
	}
	// +=
	Atribute<T>& operator+=(const Atribute<T>& other)
	{
		this->current += other.current;
		this->max += other.max;
		if (this->current > this->max)
		{
			this->current = this->max;
		}
		return *this;
	}
	Atribute<T>& operator+=(const T& value)
	{
		this->current += value;
		if (this->current > this->max)
		{
			this->current = this->max;
		}
		return *this;
	}
	// -=
	Atribute<T>& operator-=(const Atribute<T>& other)
	{
		this->current -= other.current;
		this->max -= other.max;
		if (this->max < 0)
		{
			this->max = 0;
			this->current = this->max;
		}
		else if (this->current > this->max)
		{
			this->current = this->max;
		}
		else if (this->current < 0)
		{
			this->current = 0;
		}
		return *this;
	}
	Atribute<T>& operator-=(const T& value)
	{
		this->current -= value;
		if (this->current < 0)
		{
			this->current = 0;
		}
		else if (this->current > this->max)
		{
			this->current = this->max;
		}
		return *this;
	}
private:
	T current;
	T max;
};