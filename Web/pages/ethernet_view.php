<link rel="stylesheet" href="/css/main.css" type="text/css">
<link href="https://fonts.googleapis.com/css?family=Nanum+Gothic:700|Noto+Sans+KR:500&amp;subset=korean" rel="stylesheet">
<?php
  require("../conf/mysqlconn.php");
  require("../conf/phperror.php");
  header("Refresh:5");

  //쿼리부
  $qry1 = "SELECT * FROM SensTable;";
  $rst1 = mysqli_query($conn, $qry1);

  $qry3 = "SELECT * FROM SensTable ORDER BY idx3 DESC LIMIT 10;"; //5개 조회 쿼리
  $rst3 = mysqli_query($conn, $qry3);

  //페이징 코드
  if(isset($_GET['p'])){
    $page=$_GET['p'];
  }else{
    $page=1;
  } //page값 없으면 1로 셋

  $list = 10;
  $current_page = isset($_GET['p'])? $_GET['p']:1;
  $start_num = ($current_page - 1) * $list;
  $row_num = mysqli_num_rows($rst1);
  $block_ct = 10;
  $block_num = ceil($current_page/$block_ct);
  $block_start = (($block_num - 1) * $block_ct) + 1;
  $block_end = $block_start + $block_ct - 1;
  $total_page = ceil($row_num/$list);

  if($block_end>$total_page){
  	$block_end = $total_page;
  }

  $total_block = ceil($total_page/$block_ct);

  $qry2 = "SELECT * FROM SensTable ORDER BY idx3 DESC LIMIT $start_num, $list;"; //페이징 쿼리
  $rst2 = mysqli_query($conn, $qry2);

  $t_sum = 0;  $h_sum = 0;  $s_sum = 0;

  while($row = mysqli_fetch_array($rst3)){
    $t_sum += $row['temp'];
    $h_sum += $row['humi'];
    $s_sum += $row['soil_humi'];

    $w_level = $row['water_level'];
  }

  $t_avg = $t_sum / 10;
  $h_avg = $h_sum / 10;
  $s_avg = $s_sum / 10;

  echo "<table width='700' align='center'><tr><td align='center'><img src='../img/logo.png' height='70%'></td></tr></table><table width='700' align='center' border='1' class='cc' rules='all'><tr align='center'><th>표본</th><th colspan='2'>평균 온도</th><th colspan='2'>평균 습도</th><th colspan='2'>화분 수분량</th><th>물통 높이</th></tr>";
  echo "<tr align='center'><td>10 개</td><td>".$t_avg."°C</td><td>";

  if ($t_avg<20) {
    echo "서늘해요";
  }elseif ($t_avg>27) {
    echo "더워요";
  }else{
    echo "쾌적해요";
  }

  echo "</td><td>".$h_avg."%</td><td>";

  if ($h_avg<40) {
    echo "건조해요";
  }elseif ($h_avg>65) {
    echo "습해요";
  }else{
    echo "쾌적해요";
  }

  echo "</td><td>".$s_avg."%</td><td>";

  if ($s_avg<30) {
    echo "말랐어요";
  }elseif ($s_avg>70) {
    echo "축축해요";
  }else{
    echo "적당해요";
  }

  echo "</td><td>";

  if ($w_level<400) {
    echo "부족해요";
  }elseif ($w_level>70) {
    echo "축축해요";
  }else{
    echo "적당해요";
  }

  echo "</td></tr></table><br>";

  echo "<table width='700' align='center' border='1' class='cc' rules='all'><tr align='center'><th>idx</th><th>습도</th><th>온도</th><th>조도값</th><th>토양수분</th><th>물통 수위</th><th>탁함 정도</th><th>time</th></tr>";

  while($row = mysqli_fetch_array($rst2)){
  	echo "<tr align='center'><td>".$row['idx3']."</td><td>";

  	if($row['humi']<40){
  		echo "건조</td><td>";
  	}elseif($row['humi']<60){
  		echo "쾌적</td><td>";
  	}else{
  		echo "습함</td><td>";
  	}

  	echo $row['temp']."°C</td><td>";

  	if($row['v_light']>=500){
  		echo "어두움</td><td>";
  	}else{
  		echo "밝음</td><td>";
  	}


  	echo $row['soil_humi']."%</td><td>";

  	if($row['water_level']<400){
  		echo "<font color='red'>물양 부족</font></td><td>";
  	}elseif($row['water_level']<550){
  		echo "물양 적정</td><td>";
  	}else{
  		echo "물양 충분</td><td>";
  	}

  	if($row['water_tds']<300){
  		echo "맑음</td><td>";
  	}else{
  		echo "<font color='red'>탁함</font></td><td>";
  	}

  	echo $row['time']."</td></tr>";
  }

  echo "</table><br><center>";

  //하단부 페이징
  if($page <= 1){
  }else{
    $pre = $page - 1;
    echo "<a href='data_view.php?p=1' style='text-decoration:none'> 처음 </a>";

    if($block_num == $block_start){
    }else{
      $pre_block_start = $block_start-1;
      echo "<a href='data_view.php?p=".$pre_block_start."' style='text-decoration:none'> << </a>";
    }
    echo "<a href='data_view.php?p=".$pre."' style='text-decoration:none'> ＜ </a>";
  }

  for($i = $block_start; $i <= $block_end; $i++){ //각 페이지 별 링크
    if($page == $i){
      echo "<font color='#168'><b> [$i] </b></a>";
    }else{
      echo "<a href='data_view.php?p=".$i."' style='text-decoration:none'> ".$i." </a>";
    }
  }

  if($block_num >= $total_block){ //만약 현재 블록이 블록 총개수보다 크거나 같다면 빈 값
  }else{
    $next = $page + 1; //next변수에 page + 1을 해준다.
    echo "<a href='data_view.php?p=".$next."' style='text-decoration:none'> ＞ </a>"; //다음글자에 next변수를 링크, 현재 4페이지면 +1하여 5페이지로 이동
    if($block_num == $block_end){
    }else{
      $next_block_end = $block_end + 1;
      echo "<a href='data_view.php?p=".$next_block_end."' style='text-decoration:none'> >> </a>";
    }
  }

  if($page >= $total_page){ //만약 page가 페이지수보다 크거나 같다면
  }else{
    echo "<a href='data_view.php?p=".$total_page."' style='text-decoration:none'> 끝 </a>"; //아니라면 마지막글자에 total_page를 링크한다.
  }

  echo "</center>";
?>
