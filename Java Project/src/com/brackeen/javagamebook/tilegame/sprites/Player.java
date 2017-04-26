package com.brackeen.javagamebook.tilegame.sprites;

import com.brackeen.javagamebook.graphics.Animation;
import com.brackeen.javagamebook.test.GameCore;

/**
    The Player.
*/
public class Player extends Creature {

    private static final float JUMP_SPEED = -.95f;

    private boolean onGround;
    public int health = 20;
    private int maxhealth = 40;

    public Player(Animation left, Animation right,
        Animation deadLeft, Animation deadRight)
    {
        super(left, right, deadLeft, deadRight);
    }


    public void collideHorizontal() {
        setVelocityX(0);
    }


    public void collideVertical() {
        // check if collided with ground
        if (getVelocityY() > 0) {
            onGround = true;
        }
        setVelocityY(0);
    }


    public void setY(float y) {
        // check if falling
        if (Math.round(y) > Math.round(getY())) {
            onGround = false;
        }
        super.setY(y);
    }


    public void wakeUp() {
        // do nothing
    }


    /**
        Makes the player jump if the player is on the ground or
        if forceJump is true.
    */
    public void jump(boolean forceJump) {
        if (onGround || forceJump) {
            onGround = false;
            setVelocityY(JUMP_SPEED);
        }
    }


    public float getMaxSpeed() {
        return 0.5f;
    }

    public int getHealth(){
    	int xval = Math.round(Math.abs(getVelocityX()));
    	if(xval == 0 && onGround == true){
    		if(GameCore.timecounter >= 1000){
        		health+=5;
        		GameCore.timecounter = 0;
        	}
    	}
    	else if(xval != 0 || onGround == false){
    		if(GameCore.timecounter >= 900){
        		health+=1;
        		GameCore.timecounter = 0;
        	}
    	}
    	return health;	
    }
}
