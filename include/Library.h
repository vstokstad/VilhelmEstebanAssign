//Stolen from Oliver Lebert;
//Added Vector3 with similar operators as V2;
//Added Lerp function for floats and Vector3;


#pragma once

#include <cmath>



struct Vector3
{
	float x;
	float y;
	float z;

public:
	Vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}


	float sqrMagnitude() const
	{
		return x * x + y * y + z * z;
	}

	float magnitude() const
	{
		return sqrt(sqrMagnitude());
	}

	void Normalize()
	{
		float length = magnitude();
		if (length > 0) {
			x /= length;
			y /= length;
			z /= length;
		}
	}

	Vector3 normalized() const
	{
		float length = magnitude();
		Vector3 vector = Vector3(x, y, z);
		if (length > 0) {
			vector.x /= length;
			vector.y /= length;
			vector.z /= length;
		}
		return vector;
	}

	static float Dot(Vector3 a, Vector3 b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

};

static Vector3 operator+(Vector3 lhs, const Vector3 rhs)
{
	return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

static Vector3 operator+(Vector3 lhs, const float rhs)
{
	return Vector3(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
}

static void operator+=(Vector3 lhs, const Vector3 rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;
}

static Vector3 operator-(Vector3 lhs, const Vector3 rhs)
{
	return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}


static Vector3 operator-(Vector3 current)
{
	return Vector3(-current.x, -current.y, -current.z);
}

static void operator-=(Vector3 lhs, const Vector3 rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;
}

static Vector3 operator*(Vector3 lhs, const float rhs)
{
	return Vector3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

static void operator*=(Vector3 lhs, const float rhs)
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	lhs.z *= rhs;
}

static Vector3 operator*(Vector3 lhs, const Vector3 rhs)
{
	return Vector3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

static void operator*=(Vector3 lhs, const Vector3 rhs)
{
	lhs.x *= rhs.x;
	lhs.y *= rhs.y;
	lhs.z *= rhs.z;
}


struct Vector2
{
public:
	Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float x;
	float y;

	float sqrMagnitude()
	{
		return x * x + y * y;
	}

	float magnitude()
	{
		return sqrt(sqrMagnitude());
	}

	void Normalize()
	{
		float length = magnitude();
		if (length > 0) {
			x /= length;
			y /= length;
		}
	}

	Vector2 normalized()
	{
		float length = magnitude();
		Vector2 vector = Vector2(x, y);
		if (length > 0) {
			vector.x /= length;
			vector.y /= length;
		}
		return vector;
	}

	static float Dot(Vector2 a, Vector2 b)
	{
		return a.x * b.x + a.y * b.y;
	}
};

static Vector2 operator+(Vector2 lhs, const Vector2 rhs)
{
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

static void operator+=(Vector2 lhs, const Vector2 rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
}

static Vector2 operator-(Vector2 lhs, const Vector2 rhs)
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

static Vector2 operator-(Vector2 current)
{
	return Vector2(-current.x, -current.y);
}

static void operator-=(Vector2 lhs, const Vector2 rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
}

static Vector2 operator*(Vector2 lhs, const float rhs)
{
	return { lhs.x * rhs, lhs.y * rhs };
}

static void operator*=(Vector2 lhs, const float rhs)
{
	lhs.x *= rhs;
	lhs.y *= rhs;
}

static Vector2 operator*(Vector2 lhs, const Vector2 rhs)
{
	return { lhs.x * rhs.x, lhs.y * rhs.y };
}

static void operator*=(Vector2 lhs, const Vector2 rhs)
{
	lhs.x *= rhs.x;
	lhs.y *= rhs.y;
}

struct Vector2Int
{
public:
	Vector2Int()
	{
		x = 0;
		y = 0;
	}

	Vector2Int(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	explicit Vector2Int(Vector2 vector)
	{
		this->x = (int)vector.x;
		this->y = (int)vector.y;
	}

	int x;
	int y;
};

class Library
{
public:
	float static clamp(float value, float min, float max)
	{
		if (value >= min && value <= max)
			return value;

		if (value < min)
			return min;

		if (value > max)
			return max;

		return 0;

	};

	float static InverseLerp(float a, float b, float value)
	{
		return (value - a) / (b - a);
	};

	float static Lerp(float a, float b, float t)
	{
		return a + t * (b - a);
	}


};
