# 01_UnrealEngine_Shooting

_A 2D Shooting Game Made With Unreal Engine_

(Screen resolution decreased for upload)

![Main](https://user-images.githubusercontent.com/57009810/211534980-30445a2f-fdc1-4d18-becc-5a05b63c6856.gif)

-------
<h2> 1. Controls </h2>

Movement - WASD 

Shoot -  Left Mouse Click 

Boost -  Left Shift

Special Power: Destroy All -  Spacebar

Special Power: Redirect All - Left Control

<h2> 2. Player Settings </h2>

![Screenshot 2023-01-10 201720](https://user-images.githubusercontent.com/57009810/211537445-24934e54-d196-409c-9d6c-80e645faee49.png)


<h3> Gun </h3>

![bullet](https://user-images.githubusercontent.com/57009810/211698159-61efea69-f00e-440a-90d8-757f85ad6022.gif)


<ins>Bullet Count</ins>

_bulletCount = 2_

![bCount2](https://user-images.githubusercontent.com/57009810/211721069-d937000f-f1d3-4110-b0a7-c00d215bad1d.png)

![bcount2](https://user-images.githubusercontent.com/57009810/211721076-cf253888-b80b-4800-8504-6b3341b44774.gif)

_bulletCount = 3_

![bCount3](https://user-images.githubusercontent.com/57009810/211721087-9889ec96-8ac0-4b31-976e-840f4307b927.png)

![bcount3](https://user-images.githubusercontent.com/57009810/211721091-c9491d25-b930-43b4-89f6-980fe54630eb.gif)

<ins> Bullet Angle </ins>

_bulletAngle = 15_

![bulletAngle15](https://user-images.githubusercontent.com/57009810/211726332-769d9643-6987-49d4-8cfe-473e672d0a45.png)

![bulletAngle15](https://user-images.githubusercontent.com/57009810/211726353-3308ffe9-cd9f-4d7b-a1ad-8b818ca65445.gif)

_bulletAngle = 60_

![bulletAngle60](https://user-images.githubusercontent.com/57009810/211726384-9633d70c-ef69-402d-bf4b-0bf3eb502687.png)

![bulletAngle60](https://user-images.githubusercontent.com/57009810/211726394-839cadb3-a1b7-40d4-b6d9-e0c0c0283344.gif)

<h3> Special Powers </h3>

<ins> Redirect </ins>

![Redirect](https://user-images.githubusercontent.com/57009810/211763941-674cc144-ad9a-4a2d-a72e-fac62cbc8dc7.gif)

<ins> Detonate </ins>

![Explode](https://user-images.githubusercontent.com/57009810/211763971-0a1b93ac-9084-4b65-bbdd-973fcefaa29b.gif)

<h2> 3. Enemy Settings </h2>

<h3> Enemy </h3>

![enemy](https://user-images.githubusercontent.com/57009810/211540549-1a8ea26a-de65-4644-86db-89bf8b611c18.png)

<ins> Enemy Follow Probability </ins>

_followProb = 0.3_

![followProbability0 3](https://user-images.githubusercontent.com/57009810/211727371-fbbcdd5d-eb4e-4062-9977-c248ac070b57.png)

![followProbability0 3](https://user-images.githubusercontent.com/57009810/211727411-05015d85-8785-4e4c-81aa-14c69691a678.gif)

_followProb = 1_

![followProbability1](https://user-images.githubusercontent.com/57009810/211728087-04c1bb7a-3d0a-4c64-8183-1cddd09e360f.png)

![followProbability1](https://user-images.githubusercontent.com/57009810/211728097-e1fcac05-93e8-4b32-a0e6-47bce2dff76e.gif)

<h3> Enemy Spawn Settings </h3>

![Screenshot 2023-01-10 201446](https://user-images.githubusercontent.com/57009810/211537535-bcc7494b-f53a-43f8-b11c-429580c327ed.png)

![Enemyspawn](https://user-images.githubusercontent.com/57009810/211540783-0ec67767-2922-41fc-acff-aab6d2c88754.png)

BP_EnemySpawn is a blueprint actor that spawns Enemy every _spawnTime_ seconds.

<h2> 4. Boss Settings </h2>

<h3> Boss</h3> 

![Boss](https://user-images.githubusercontent.com/57009810/211541566-cd2d9972-d646-4422-8f76-c31012dd33c2.png)

<h3> Move Settings </h3> 

The Boss actor is moved by a lerp (linear interpolation) function. As such, the Boss moves according to the current location, target location, speed, and time. 

![BossLerp](https://user-images.githubusercontent.com/57009810/211730046-3944a77f-719c-4547-b4e2-8fb137047257.png)

<ins>Move Time</ins>

The time it takes for the actor to get to the final location. It determines the speed of the Boss actor. 

<ins>Move Offset</ins>

The offset position from the original position. It determines the target position. 

<h3> Attack Settings </h3> 

<ins>Bullet Distance</ins>

The distance between the bullet spawn point and the Boss actor. 

_bulletDistance = 100_

![bulletDistance100](https://user-images.githubusercontent.com/57009810/211760789-b6f11023-ff80-440d-aa15-16ed73597de2.png)

![bulletDistance100](https://user-images.githubusercontent.com/57009810/211760803-43c54fab-89c7-4b4f-8b21-8c8c1df30d23.gif)

_bulletDistance = 300_

![bulletDistance300](https://user-images.githubusercontent.com/57009810/211760836-0c2f3565-254f-4e17-8719-382ebddf3f64.png)

![bulletDistance300](https://user-images.githubusercontent.com/57009810/211760849-cb488bf1-697f-4400-aeb9-cae0ad2cb992.gif)

<ins>Pattern Delay Time</ins>

The attack cycle time. 

<h3> Boss Spawn</h3>

![Screenshot 2023-01-10 201608](https://user-images.githubusercontent.com/57009810/211537832-10f1f349-854f-4e6e-b588-5e419eaff24c.png)

![Boss Spawn](https://user-images.githubusercontent.com/57009810/211541986-2e500ba5-83cd-4bc9-9cec-fcd9273277c5.png)

<ins> Boss Level Score</ins>

The amount of score to spawn the Boss. 

_bossLevelScore = 3_

![bossLevelScore3](https://user-images.githubusercontent.com/57009810/211735547-0480065b-645d-454d-8490-9cf2aa4fa023.png)

![bossLevelScore3](https://user-images.githubusercontent.com/57009810/211756863-9b84ea17-82ef-4a45-aa5c-1f917426e42d.gif)

_bossLevelScore = 6_

![bossLevelScore6](https://user-images.githubusercontent.com/57009810/211777734-2a525d5a-dd57-426c-8f2d-0cae2ded9756.png)

![bossLevelScore5](https://user-images.githubusercontent.com/57009810/211735698-2984a1a8-5fed-472b-b6d1-474a8e929fa1.gif)

<h3> Boss Bullets</h3>

The speed of the Boss' bullets.

![Enemy Bullet Settings](https://user-images.githubusercontent.com/57009810/211541553-9ba9a102-c6bb-40c6-a130-05e5383a15f1.png)

<h2> 6. Misc Settings </h2>

<h3> Kill Zone</h3> 

The actor that destroys bullets and enemys when collided with. 

![Screenshot 2023-01-10 201522](https://user-images.githubusercontent.com/57009810/211537808-4a4bdfdf-fd23-422b-95d2-c424916093ed.png)

<h3> Trap </h3> 

A Black Hole that appears and disappears at random locations. While the player is touching the Trap actor, the player cannot shoot. 

![Trap](https://user-images.githubusercontent.com/57009810/211761723-e37e0902-7603-4fa7-8b15-f3944843ef85.png)

![Trap Settings](https://user-images.githubusercontent.com/57009810/211761809-7bd0d2b4-07c3-4433-b9dd-0d2bed6e3604.png)

<ins>Teleport Time</ins>

The spawn time interval of the Trap actor.  

<h2> 6. Collision Presets</h2> 

<h4> Player </h4> 

![player](https://user-images.githubusercontent.com/57009810/211540878-478d978c-83e9-4559-a538-973483ace746.png)

<h4> Bullet </h4> 

![Bullet](https://user-images.githubusercontent.com/57009810/211541058-1e514255-7945-440e-a4b3-f59308c7d3ea.png)

<h4> Enemy </h4> 

![enemycollision](https://user-images.githubusercontent.com/57009810/211540984-97689498-c1c2-4326-81c7-de943b8ca439.png)

<h4> Boss </h4> 

![bossCol](https://user-images.githubusercontent.com/57009810/211541208-bce1ea6f-dd0b-433e-94b2-aac0d926e0f0.png)

<h4> Killzone </h4> 

![Killzonecol](https://user-images.githubusercontent.com/57009810/211541237-59ab96e2-2bf1-4ecf-9773-5d0e2fdf471c.png)

<h4> Trap </h4> 

![trapcol](https://user-images.githubusercontent.com/57009810/211541361-273e6214-b316-4d6f-aeab-71a1970823f9.png)

<h4> Shield </h4>

![Shieldcol](https://user-images.githubusercontent.com/57009810/211541310-7bd0a833-8f67-4f79-8b1a-09392970a3b2.png)
