#pragma once

class Vec2
{
public:
	Vec2() = default;
	Vec2( int x_in,int y_in );
	Vec2 operator+( const Vec2& rhs ) const;
	Vec2& operator+=( const Vec2& rhs );
	Vec2 operator*( float rhs ) const;
	Vec2& operator*=( float rhs );
	Vec2 operator-( const Vec2& rhs ) const;
	Vec2& operator-=( const Vec2& rhs );
public:
	int x;
	int y;
};