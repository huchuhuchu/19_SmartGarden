<link rel="stylesheet" href="/css/main.css" type="text/css">
<link href="https://fonts.googleapis.com/css?family=Nanum+Gothic:700|Noto+Sans+KR:500&amp;subset=korean" rel="stylesheet">

<?php

require("../conf/mysqlconn.php");
require("../conf/phperror.php");
header("Refresh:3");

$sql1 = mysqli_query($conn, "SELECT * FROM SensTable ORDER BY idx3 DESC LIMIT 1;"); //최근 레코드 1개만 조회


while($row=mysqli_fetch_array($sql1)){
  $t = $row['temp'];  //현재 온도
  $h = $row['humi'];  //현재 습도
  $s = $row['soil_humi'];  //현재 토양 습도
  $w = $row['water_level']; //현재 수위
}
//style='border-left:1;border-right:1;border-bottom:0;border-top:1'
echo "<center><table width='95%' height='auto'><tr align='center'><td colspan='2'><img src='../img/logo.png' height='95%'></td></tr><tr height='20px' style='border=top:1'><th valign=bottom class=bb><img src='../img/text1.png'></th><th valign=bottom><img src='../img/text2.png'></th></tr><td align=center>";

//평균 온도 값
if($t<20){ //20도 이하
  echo "<img src='../img/icon_cold.png' width=90% height=auto><br><font size=6>".$t;
}elseif($t>27){  //27도 이상
  echo "<img src='../img/icon_hot.png' width=90% height=auto><br><font size=6>".$t;
}else{  //적정 온도
  echo"<img src='../img/icon_good.png' width=90% height=auto><br><font size=6>".$t;
}
echo "°C</font></td><td align=center>";

//평균 습도 값
if($h<40){ //20도 이하
  echo "<img src='../img/icon_dry.png' width=90% height=auto><br><font size=6>".$h;
}elseif($h>65){  //27도 이상
  echo "<img src='../img/icon_wet.png' width=90% height=auto><br><font size=6>".$h;
}else{  //적정 온도
  echo"<img src='../img/icon_good.png' width=90% height=auto><br><font size=6>".$h;
}
echo "%</font></td><tr><td colspan=2 height=50px></td></tr><tr height='60px'><th valign=bottom><img src='../img/text3.png'></th><th valign=bottom><img src='../img/text4.png'></th></tr><tr><td align=center>";

//평균 습도 값
if($s<40){ //20도 이하
  echo "<img src='../img/icon_dry.png' width=90% height=auto><br><font size=6>".$s;
}elseif($s>65){  //27도 이상
  echo "<img src='../img/icon_wet.png' width=90% height=auto><br><font size=6>".$s;
}else{  //적정 온도
  echo"<img src='../img/icon_good.png' width=90% height=auto><br><font size=6>".$s;
}
echo "%</font></td><td align=center>";

//물통 수위 값
if($w<400){ //20도 이하
  echo "<img src='../img/icon_low.png' width=90% height=auto><br><font size=6>물 부족</font>";
}elseif($w>550){  //27도 이상
  echo "<img src='../img/icon_full.png' width=90% height=auto><br><font size=6>물 너무 많음</font>";
}else{
    echo "<img src='../img/icon_good.png' width=90% height=auto><br><font size=6>물양 적당</font>";
  }
echo "</td></tr></table></center>";
