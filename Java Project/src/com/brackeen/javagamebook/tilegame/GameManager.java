package com.brackeen.javagamebook.tilegame;

import java.awt.*;
import java.awt.event.KeyEvent;
import java.util.Iterator;
import java.util.Scanner;

import javax.sound.midi.Sequence;
import javax.sound.midi.Sequencer;
import javax.sound.sampled.AudioFormat;

import com.brackeen.javagamebook.graphics.*;
import com.brackeen.javagamebook.sound.*;
import com.brackeen.javagamebook.input.*;
import com.brackeen.javagamebook.test.GameCore;
import com.brackeen.javagamebook.tilegame.sprites.*;

/**
    GameManager manages all parts of the game.
*/
public class GameManager extends GameCore {
	private static String filename;
	private static boolean input_map = false;
    public static void main(String[] args) {
    	Scanner input = new Scanner(System.in);
    	System.out.println("Please select the game map");
    	while(true) {
    		System.out.println("(1)Default Map");
    		System.out.println("(2)Customized Map");
    		String option = input.nextLine();
    		if (option.equals("1")){
    			break;
    		}else if (option.equals("2")){
    			input_map = true;
    			System.out.println("Please enter filename:");
        		filename = input.nextLine();
    			break;
    		} else {
    			System.out.println("Please enter the correct option");
    		}
    		
    	}
        new GameManager().run();
    }

    // uncompressed, 44100Hz, 16-bit, mono, signed, little-endian
    private static final AudioFormat PLAYBACK_FORMAT =
        new AudioFormat(44100, 16, 1, true, false);

    private static final int DRUM_TRACK = 1;

    public static final float GRAVITY = 0.002f;

    private Point pointCache = new Point();
    private TileMap map;
    private MidiPlayer midiPlayer;
    private SoundManager soundManager;
    private ResourceManager resourceManager;
    private Sound prizeSound;
    private Sound boopSound;
    private Sound shootsound;
    private Sound deadcreature;
    private Sound mushroo;
    private InputManager inputManager;
    private TileMapRenderer renderer;

    private GameAction moveLeft;
    private GameAction moveRight;
    private GameAction jump;
    private GameAction exit;
    private GameAction shoot;
    private GameAction moveDown;
    
    private int shootCount = 0;
    private long shootTime = System.currentTimeMillis();
    private boolean shootStatus = false;
    private long creatureShootTime = System.currentTimeMillis();
    private boolean creatureShootStatus = false;
    private boolean shootFrozen = false;
    private boolean lastMove = true;
    private long pressCount = 0;
    private long pressTime = System.currentTimeMillis();
    private long invincibleTime = System.currentTimeMillis();
    private boolean hold = false;
    private boolean invincibleState = false;
    private boolean poisonstate = false;
    private long poisonTime = System.currentTimeMillis();
    


    public void init() {
        super.init();

        // set up input manager
        initInput();

        // start resource manager
        resourceManager = new ResourceManager(
        screen.getFullScreenWindow().getGraphicsConfiguration());

        // load resources
        renderer = new TileMapRenderer();
        renderer.setBackground(
            resourceManager.loadImage("background.png"));

        // load first map
        if (input_map) {
        	map = resourceManager.loadCustomizedMap(filename);
        } else {
        	map = resourceManager.loadNextMap();
        }

        // load sounds
        soundManager = new SoundManager(PLAYBACK_FORMAT);
        prizeSound = soundManager.getSound("sounds/prize.wav");
        boopSound = soundManager.getSound("sounds/boop2.wav");
        shootsound = soundManager.getSound("sounds/hit.wav");
        deadcreature = soundManager.getSound("sounds/dead.wav");
        mushroo = soundManager.getSound("sounds/dead.wav");

        // start music
        midiPlayer = new MidiPlayer();
        Sequence sequence =
            midiPlayer.getSequence("sounds/music.midi");
        midiPlayer.play(sequence, true);
        toggleDrumPlayback();
    }


    /**
        Closes any resurces used by the GameManager.
    */
    public void stop() {
        super.stop();
        midiPlayer.close();
        soundManager.close();
    }


    private void initInput() {
        moveLeft = new GameAction("moveLeft");
        moveRight = new GameAction("moveRight");
        shoot = new GameAction("shoot");
        jump = new GameAction("jump",
            GameAction.DETECT_INITAL_PRESS_ONLY);
        moveDown = new GameAction("moveDown");
        exit = new GameAction("exit",
            GameAction.DETECT_INITAL_PRESS_ONLY);

        inputManager = new InputManager(
            screen.getFullScreenWindow());
        inputManager.setCursor(InputManager.INVISIBLE_CURSOR);

        inputManager.mapToKey(moveLeft, KeyEvent.VK_LEFT);
        inputManager.mapToKey(moveRight, KeyEvent.VK_RIGHT);
        inputManager.mapToKey(shoot, KeyEvent.VK_S);
        inputManager.mapToKey(jump, KeyEvent.VK_UP);
        inputManager.mapToKey(moveDown, KeyEvent.VK_DOWN);
        inputManager.mapToKey(exit, KeyEvent.VK_ESCAPE);
    }


    private void checkInput(long elapsedTime) {

        if (exit.isPressed()) {
            stop();
        }

        Player player = (Player)map.getPlayer();
        if (player.isAlive()) {
            float velocityX = 0;
            float velocityY = 0;
            if (moveLeft.isPressed()) {
                velocityX-=player.getMaxSpeed();
                lastMove = false;
            }
            if (moveRight.isPressed()) {
                velocityX+=player.getMaxSpeed();
                lastMove = true;
            }
            if (moveDown.isPressed()) {
                velocityY+=player.getMaxSpeed();
                player.setVelocityY(velocityY + 1);
                
            }
            if (jump.isPressed()) {
                player.jump(false);
            }
            if (shoot.isPressed()) {
            	
            	if (System.currentTimeMillis() - pressTime < 50) {
            		pressCount++;
            	} else {
            		pressCount = 0;
            	}
            	pressTime = System.currentTimeMillis();
            	System.out.println(pressCount);
            	if (pressCount == 80) {
            		hold = true;
            		pressCount =0;
            	}
            	if (!hold) {
            		shootAction();
            	}
            		
            }
            player.setVelocityX(velocityX);
        }

    }
    
    private void shootAction() {
    	
    	if (!shootFrozen) {
    		if (hold) {
    			if (shootCount <= 10) {
    				if (System.currentTimeMillis() - shootTime >= 500) {
    					shootCount+=1;
    					shootStatus = true;
    					shootTime = System.currentTimeMillis();
    				}
    			} else {
    				shootFrozen = true;
    				hold = false;
    			}
    		} else {
    			if (System.currentTimeMillis() - shootTime >= 500) {
					shootCount+=1;
					shootStatus = true;
					shootTime = System.currentTimeMillis();
				}
    		}
    	} else if (System.currentTimeMillis() - shootTime >= 1000) {
    		shootFrozen = false;
    		hold = false;
    		shootCount = 0;
    		shootStatus = true;
    	}
    	
    }
    

    public void draw(Graphics2D g) {
    	
        renderer.draw(g, map,
            screen.getWidth(), screen.getHeight());
        Player player = (Player) map.getPlayer();
        g.setColor(Color.green);
        g.setFont(new Font("Calibri",0,25));
        int healthbar = player.getHealth();
        if (player.getHealth()>40){
        	healthbar = 40;
        }
        else if (player.getHealth()<0){
        	healthbar = 0;
        }
        g.drawString("HP: "+ healthbar,50, 25);
        if (invincibleState == true){
        	g.drawString("INVINCIBLE",500,100);
        }
        else if(poisonstate == true){
        	g.drawString("POISON", 500, 100);
        }
    }


    /**
        Gets the current map.
    */
    public TileMap getMap() {
        return map;
    }


    /**
        Turns on/off drum playback in the midi music (track 1).
    */
    public void toggleDrumPlayback() {
        Sequencer sequencer = midiPlayer.getSequencer();
        if (sequencer != null) {
            sequencer.setTrackMute(DRUM_TRACK,
                !sequencer.getTrackMute(DRUM_TRACK));
        }
    }


    /**
        Gets the tile that a Sprites collides with. Only the
        Sprite's X or Y should be changed, not both. Returns null
        if no collision is detected.
    */
    public Point getTileCollision(Sprite sprite,
        float newX, float newY)
    {
        float fromX = Math.min(sprite.getX(), newX);
        float fromY = Math.min(sprite.getY(), newY);
        float toX = Math.max(sprite.getX(), newX);
        float toY = Math.max(sprite.getY(), newY);

        // get the tile locations
        int fromTileX = TileMapRenderer.pixelsToTiles(fromX);
        int fromTileY = TileMapRenderer.pixelsToTiles(fromY);
        int toTileX = TileMapRenderer.pixelsToTiles(
            toX + sprite.getWidth() - 1);
        int toTileY = TileMapRenderer.pixelsToTiles(
            toY + sprite.getHeight() - 1);

        // check each tile for a collision
        for (int x=fromTileX; x<=toTileX; x++) {
            for (int y=fromTileY; y<=toTileY; y++) {
                if (x < 0 || x >= map.getWidth() ||
                    map.getTile(x, y) != null)
                {
                    // collision found, return the tile
                    pointCache.setLocation(x, y);
                    return pointCache;
                }
            }
        }

        // no collision found
        return null;
    }


    /**
        Checks if two Sprites collide with one another. Returns
        false if the two Sprites are the same. Returns false if
        one of the Sprites is a Creature that is not alive.
    */
    public boolean isCollision(Sprite s1, Sprite s2) {
        // if the Sprites are the same, return false
        if (s1 == s2) {
            return false;
        }

        // if one of the Sprites is a dead Creature, return false
        if (s1 instanceof Creature && !((Creature)s1).isAlive()) {
            return false;
        }
        if (s2 instanceof Creature && !((Creature)s2).isAlive()) {
            return false;
        }

        // get the pixel location of the Sprites
        int s1x = Math.round(s1.getX());
        int s1y = Math.round(s1.getY());
        int s2x = Math.round(s2.getX());
        int s2y = Math.round(s2.getY());

        // check if the two sprites' boundaries intersect
        return (s1x < s2x + s2.getWidth() &&
            s2x < s1x + s1.getWidth() &&
            s1y < s2y + s2.getHeight() &&
            s2y < s1y + s1.getHeight());
    }


    /**
        Gets the Sprite that collides with the specified Sprite,
        or null if no Sprite collides with the specified Sprite.
    */
    public Sprite getSpriteCollision(Sprite sprite) {

        // run through the list of Sprites
        Iterator i = map.getSprites();
        while (i.hasNext()) {
            Sprite otherSprite = (Sprite)i.next();
            if (isCollision(sprite, otherSprite)) {
                // collision found, return the Sprite
                return otherSprite;
            }
        }

        // no collision found
        return null;
    }


    /**
        Updates Animation, position, and velocity of all Sprites
        in the current map.
    */
    public void update(long elapsedTime) {
        Player player = (Player)map.getPlayer();
        Creature bullet = (Creature)resourceManager.getBullet().clone();
        Creature creatureBullet = (Creature)resourceManager.getCreatureBullet().clone();
        
        
        if (player.health <= 0) {
        	player.setState(Creature.STATE_DYING);
        	player.setState(Creature.STATE_DEAD);
        }
        // player is dead! start map over
        if (player.getState() == Creature.STATE_DEAD) {
            map = resourceManager.reloadMap();
            return;
        }

        // get keyboard/mouse input
        checkInput(elapsedTime);

        // update player
        updateCreature(player, elapsedTime);
        player.update(elapsedTime);
        
        // generate bullet
        if (hold) {
        	shootAction();
        }
        if (shootStatus) {
        	shootStatus = false;
        	bullet.setY(player.getY());
        	bullet.setX(player.getX());
        	bullet.setVelocityY(0);
        	if(lastMove) {
        		bullet.setVelocityX(1.0f);
        	} else {
        		bullet.setVelocityX(-1.0f);
        	}
        	map.addSprite(bullet);
        	soundManager.play(shootsound);
        }
        

        // update other sprites
        Iterator i = map.getSprites();
        while (i.hasNext()) {
            Sprite sprite = (Sprite)i.next();
            if (sprite instanceof Creature) {
                Creature creature = (Creature)sprite;
                if (creature instanceof Grub && Math.abs(creature.getX()-player.getX()) < 500) {
                	if (player.getX() - creature.getX() < 0) {
                		if (creature.getVelocityX() > 0){
                			creature.setVelocityX(-creature.getVelocityX()) ;
                		}
                	} else {
                		if (creature.getVelocityX() < 0){
                			creature.setVelocityX(-creature.getVelocityX()) ;
                		}
                	}
                	//generate creatureBullet
                	creatureShootStatus = true;
                	if (System.currentTimeMillis() - creatureShootTime >1000) {
                		creatureBullet.setY(creature.getY());
                		creatureBullet.setX(creature.getX());
                		creatureBullet.setVelocityY(0);
                		if(creature.getVelocityX() > 0) {
                			creatureBullet.setVelocityX(0.5f);
                		} else {
                			creatureBullet.setVelocityX(-0.5f);
                		}
                		creatureShootTime = System.currentTimeMillis();
                	}
                	
                	
                }
                if (creature.getState() == Creature.STATE_DEAD) {
                    i.remove();
                }
                else {
                    updateCreature(creature, elapsedTime);
                }
            }
            
            // normal update
            sprite.update(elapsedTime);
        }
        if(creatureShootStatus){
        	map.addSprite(creatureBullet);
        }
    }

    /**
        Updates the creature, applying gravity for creatures that
        aren't flying, and checks collisions.
    */
    private void updateCreature(Creature creature,
        long elapsedTime)
    {
    	Player player = (Player)map.getPlayer();
    	if (System.currentTimeMillis() - invincibleTime > 1000) {
    		invincibleState = false;
    	}
    	if (System.currentTimeMillis() - poisonTime > 1000) {
    		poisonstate = false;
    	}
        // apply gravity
        if (!creature.isFlying() && !(creature instanceof Bullet) && !(creature instanceof CreatureBullet) ) {
            creature.setVelocityY(creature.getVelocityY() +
                GRAVITY * elapsedTime);
        }

        // change x
        float dx = creature.getVelocityX();
        float oldX = creature.getX();
        float newX = oldX + dx * elapsedTime;
        Point tile =
            getTileCollision(creature, newX, creature.getY());
        if (tile == null) {
            creature.setX(newX);
        } else if(creature instanceof Bullet || creature instanceof CreatureBullet){
        	creature.setState(Creature.STATE_DEAD);
        } else {
        	
            // line up with the tile boundary
            if (dx > 0) {
                creature.setX(
                    TileMapRenderer.tilesToPixels(tile.x) -
                    creature.getWidth());
            }
            else if (dx < 0) {
                creature.setX(
                    TileMapRenderer.tilesToPixels(tile.x + 1));
            }
            creature.collideHorizontal();
        }
        if (creature instanceof Player) {        	
            checkPlayerCollision((Player)creature, false);
        }
        if (creature instanceof Bullet) {
        	Sprite collisionSprite = getSpriteCollision(creature);
        	if (collisionSprite instanceof Grub || collisionSprite instanceof Fly) {
        		Creature badguy = (Creature)collisionSprite;
        		// kill the badguy and make player bounce
        		soundManager.play(deadcreature);
        		player.health+=10;
        		badguy.setState(Creature.STATE_DYING);
        		creature.setState(Creature.STATE_DEAD);
        	}
        }
        if (creature instanceof Grub || creature instanceof Fly) {
        	Sprite collisionSprite = getSpriteCollision(creature);
            if (collisionSprite instanceof PowerUp.Gas || collisionSprite instanceof PowerUp.Explode) {
            	if (Math.round(creature.getVelocityY()) >= 0 && creature.getY() < collisionSprite.getY()) {
            		player.setVelocityY(0);
            	} else if (creature.getVelocityX() > 0 && creature.getX() < collisionSprite.getX()) {
            		creature.setX(collisionSprite.getX() - collisionSprite.getWidth());
            	} else if (creature.getVelocityX() < 0 && creature.getX() > collisionSprite.getX()) {
            		creature.setX(collisionSprite.getX() + collisionSprite.getWidth());
            	}
            }
        }

        // change y
        float dy = creature.getVelocityY();
        float oldY = creature.getY();
        float newY = oldY + dy * elapsedTime;
        tile = getTileCollision(creature, creature.getX(), newY);
        if (tile == null) {
            creature.setY(newY);
        }
        else {
            // line up with the tile boundary
            if (dy > 0) {
                creature.setY(
                    TileMapRenderer.tilesToPixels(tile.y) -
                    creature.getHeight());
            }
            else if (dy < 0) {
                creature.setY(
                    TileMapRenderer.tilesToPixels(tile.y + 1));
            }
            creature.collideVertical();
        }
        if (creature instanceof Player) {
            boolean canKill = (oldY < creature.getY());
            checkPlayerCollision((Player)creature, canKill);
        }
        

    }


    /**
        Checks for Player collision with other Sprites. If
        canKill is true, collisions with Creatures will kill
        them.
    */
    public void checkPlayerCollision(Player player,
        boolean canKill)
    {
        if (!player.isAlive()) {
            return;
        }

        // check for player collision with other sprites
        Sprite collisionSprite = getSpriteCollision(player);
        if (collisionSprite instanceof PowerUp.Gas) {
        	shootFrozen = true;
        	poisonstate = true;
        	poisonTime = System.currentTimeMillis();
        	shootTime = System.currentTimeMillis();
        	if (Math.round(player.getVelocityY()) >= 0 && player.getY() < collisionSprite.getY()) {
        		player.setVelocityY(0);
        	} else if (player.getVelocityX() > 0 && player.getX() < collisionSprite.getX()) {
        		player.setX(collisionSprite.getX() - collisionSprite.getWidth());
        	} else if (player.getVelocityX() < 0 && player.getX() > collisionSprite.getX()) {
        		player.setX(collisionSprite.getX() + collisionSprite.getWidth());
        	}
        } else if (collisionSprite instanceof PowerUp.Explode) {
        	player.health-=10;
        	map.removeSprite(collisionSprite);
        } else if (collisionSprite instanceof PowerUp.Mushroom) {
        	player.health+=5;
        	soundManager.play(mushroo);
        	map.removeSprite(collisionSprite);
        } else if (collisionSprite instanceof PowerUp) {
            acquirePowerUp((PowerUp)collisionSprite);        
        } else if (collisionSprite instanceof CreatureBullet){
        	player.health-=5;
        	map.removeSprite(collisionSprite);
        } else if (collisionSprite instanceof Creature && !(collisionSprite instanceof Bullet) && !(collisionSprite instanceof PowerUp.Gas)) {
            Creature badguy = (Creature)collisionSprite;
            if (canKill) {
                // kill the badguy and make player bounce
                soundManager.play(boopSound);
                badguy.setState(Creature.STATE_DYING);
                player.setY(badguy.getY() - player.getHeight());
                player.jump(true);
                player.health+=10;
            } else if (invincibleState) {
            	soundManager.play(boopSound);
                badguy.setState(Creature.STATE_DYING);
          
            }
            else {
                // player dies! gai le!!!!!!!!!!!!!!!!!!!!!!
            	player.setState(Creature.STATE_DYING);
            }
        }
    }


    /**
        Gives the player the speicifed power up and removes it
        from the map.
    */
    public void acquirePowerUp(PowerUp powerUp) {
    	if (!(powerUp instanceof PowerUp.Gas)) {
    		// remove it from the map
    		map.removeSprite(powerUp);
    	}

        if (powerUp instanceof PowerUp.Star) {
            invincibleState = true;
            invincibleTime = System.currentTimeMillis();
            soundManager.play(prizeSound);
        }
        else if (powerUp instanceof PowerUp.Music) {
            // change the music
            soundManager.play(prizeSound);
            toggleDrumPlayback();
        }
        else if (powerUp instanceof PowerUp.Goal) {
            // advance to next map
            soundManager.play(prizeSound,
                new EchoFilter(2000, .7f), false);
            map = resourceManager.loadNextMap();
        }
    }

}
