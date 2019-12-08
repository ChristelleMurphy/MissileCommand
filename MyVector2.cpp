#include "MyVector2.h"

/// <summary>
/// get length of vector using sqrt of the sum of the squares
/// </summary>
/// <param name="t_vector">input vector</param>
/// <returns>length</returns>
float vectorLength(sf::Vector2f t_vector)
{
	float sumOfSquares = (t_vector.x * t_vector.x ) + (t_vector.y * t_vector.y);
	const float length = std::sqrt(sumOfSquares);
	return length;
}

float vectorLengthSquared(sf::Vector2f t_vector)
{
	//x2+y2
	float answer = (t_vector.x * t_vector.x + t_vector.y * t_vector.y);
	return answer;
}

float vectorCorssProduct(sf::Vector2f t_vectorA, sf::Vector2f t_VectorB)
{
	float answer = (t_vectorA.x * t_VectorB.y - t_vectorA.y * t_VectorB.x);
	return answer;
}

float vectorDotProduct(sf::Vector2f t_vectorA, sf::Vector2f t_VectorB)
{
	float answer = (t_vectorA.x * t_VectorB.x + t_vectorA.y * t_VectorB.y);
	return answer;
}

float vectorAngleBetween(sf::Vector2f t_vectorA, sf::Vector2f t_VectorB)
{
	float angle = acosf(vectorDotProduct(vectorUnitVector(t_vectorA), vectorUnitVector(t_vectorA)));
	if (angle > 0.1f)
		angle = 0.1f;
	if (angle < -0.1f)
		angle = -0.1f;
	float angleInRadians = angle * PI / 180;
	return angleInRadians;
}

sf::Vector2f vectorRotateBy(sf::Vector2f t_vector, float t_angleRadians)
{
	float cos = std::cos(t_angleRadians);
	float sin = std::sin(t_angleRadians);
	float xCoOrd = 0;
	float yCoOrd = 0;
	xCoOrd = (t_vector.x*cos) - (t_vector.x*sin);
	yCoOrd = (t_vector.y*sin) + (t_vector.y*cos);
	sf::Vector2f result{ xCoOrd, yCoOrd };
	return result;
}


sf::Vector2f vectorProjection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	//the vector projection is the unit vector a/|a | times the scalar projection of b onto a 
	sf::Vector2f answer = vectorScalarProjection(t_vector, t_onto) * vectorUnitVector(t_onto);
	return answer;
}

sf::Vector2f vectorRejection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	sf::Vector2f answer = t_vector - vectorProjection(t_vector, t_onto);
	return answer;
}

float vectorScalarProjection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	float answer = vectorDotProduct(t_vector, t_onto)/vectorLength(t_onto);
	return answer;
}

sf::Vector2f vectorUnitVector(sf::Vector2f t_vector)
{
	sf::Vector2f result{ 0.0f,0.0f };
	const float lenght = vectorLength(t_vector);
	if (lenght != 0.0f) // never divide by zero unless the zombies are overrunning the base
	{
		result = sf::Vector2f{ t_vector.x / lenght, t_vector.y / lenght };
	}
	return result;
}
