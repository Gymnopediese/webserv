/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.js                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 12:00:01 by albaud            #+#    #+#             */
/*   Updated: 2023/05/20 10:43:01 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

var X = 800
var Y = 500
class Player
{
	constructor(x, y) {
		this.x = x;
		this.y = y;
		this.score = 0;
	}
}

var mousePos ={
	x: 20,
	y: 150,
};
var PADDLE_X = 20
var PADDLE_Y = 100
var RADIUS = 10
var SPEED = 3
var pos = new obj(new vect(X / 2, Y / 2), new vect(1, 1))
var s = 0
var canvas = document.getElementById("myCanvas");
var players = [
	new Player(PADDLE_X, Y / 2),
	new Player(X - PADDLE_X * 2, Y / 2),
]


function getMousePos(canvas, evt) {
	var rect = canvas.getBoundingClientRect();
	return {
	  x: evt.clientX - rect.left,
	  y: evt.clientY - rect.top
	};
}

function vect(x, y) {
	this.x = x;
	this.y = y;
}

function obj(pos, vitess) {
	this.pos = pos;
	this.vitess = vitess;
}

canvas.addEventListener("mousemove", function (evt) {
	mousePos = getMousePos(canvas, evt);
}, false);

function is_in_box(x, y, player)
{
	return (x > player.x
			&& x < player.x + PADDLE_X
			&& y > player.y
			&& y < player.y + PADDLE_Y)
}

function collid()
{
	var r = 0;
	while (r < 2 * Math.PI)
	{
		x = Math.cos(r) * RADIUS + pos.pos.x
		y = Math.sin(r) * RADIUS + pos.pos.y
		//console.log(x, y);
		for (var i = 0; i < 2; i++)
		{
			if (is_in_box(x, y, players[i]))
			{
				return (players[i]);
			}
		}
		r += 0.05;
	}
	return (false)
}

function	normalize(vector)
{
	var l = Math.sqrt(vector.x * vector.x + vector.y * vector.y)

	vector.x /= l;
	vector.y /= l;
	return (vector);
}

function	draw_ball(ctx)
{
	ctx.arc(pos.pos.x, pos.pos.y, RADIUS, 0, 2 * Math.PI);
	pos.pos.x += pos.vitess.x
	var player = collid(players)
	if (player)
	{
		var new_x = ((player.y + PADDLE_Y - pos.pos.y) / PADDLE_Y) - 0.5

		console.log(new_x);
		pos.pos.x -= pos.vitess.x
		if (player.x > X / 2)
		{
			pos.vitess.y = -new_x
			pos.vitess.x = new_x - 0.5
		}
		else
		{
			pos.vitess.y = -new_x
			pos.vitess.x = 0.5 - new_x
		}
	}
	else if (pos.pos.x - RADIUS < 0 || pos.pos.x + RADIUS > X)
	{
		pos.pos.x = X / 2;
		pos.pos.y = Y / 2;
	}
	pos.pos.y += pos.vitess.y
	if (collid(players))
	{
		console.log("alaur");
		pos.pos.y -= pos.vitess.y
		pos.vitess.y -= 2
	}
	else if (pos.pos.y + RADIUS > Y)
	{
		pos.pos.y -= pos.vitess.y
		pos.vitess.y -= 2
	}
	else if (pos.pos.y - RADIUS < 0)
	{
		pos.pos.y -= pos.vitess.y
		pos.vitess.y += 2
	}
	pos.vitess = normalize(pos.vitess);
	pos.vitess.x *= SPEED;
	pos.vitess.y *= SPEED;
}

function draw() {

	var ctx = canvas.getContext("2d");
	ctx.beginPath();
	ctx.clearRect(0,0,X,Y);
	draw_ball(ctx);
	players[0].y = mousePos.y
	ctx.rect(players[0].x, players[0].y, PADDLE_X, PADDLE_Y);

	players[1].y += (pos.pos.y - PADDLE_Y - players[1].y) / ((Math.random() * 10) + 15)


	ctx.rect(players[1].x, players[1].y, PADDLE_X, PADDLE_Y);
	ctx.stroke();
  }
setInterval(function() {
	draw();
  }, 1);