# 주사위 윷놀이

잏잏......이런 윷놀이를 누가 한단 말임 



#### 맵 만들기

![image](https://user-images.githubusercontent.com/49193546/76166774-709ba200-61a4-11ea-81b9-9191a3c907dd.png)

이렇게 맵 구성함 

파란색인 부분에서는 꺾을 수 있으니까 꺾어지는 정보 turn 에 저장!

나머지 움직이는 부분은 moveMap에 저장

### 점수는 score에 저장! 근데 도착했을 때 점수 0점임🪓🔪 이딴 게임 누가해

진짜 말도 안되네....



~~~c++
				int moveStart = cur;
        if(turn[moveStart] != 0 ){
            moveNum-=1;
            moveStart = turn[moveStart];
        }

        while(1){
            if(moveNum == 0 ) break;
            moveStart = moveMap[moveStart];
            moveNum -= 1;
        }
~~~

일단 지금 자리가 꺾일 수 있는 자리면 꺾어서 가버리고 그 다음부터 moveMap으로 돌림



