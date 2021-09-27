<?php
$x1 = -2.1;
$x2 = 0.6;
$y1 = -1.2;
$y2 = 1.2;
$zoom = 100;
$iterations_max = 50;

$image_x = ($x2 - $x1)*$zoom;
$image_y = ($y2 - $y1)*$zoom;

// on créé l'image et les couleurs, inutile ici de remplire l'image vu que on dessinera tous les pixels
$image = imagecreatetruecolor($image_x, $image_y);
$blanc = imagecolorallocate($image, 255, 255, 255);
$noir  = imagecolorallocate($image, 0, 0, 0);
imagefill($image, 0 ,0 , $blanc);

// on définit la liste des couleurs du dégradé ici, ça évite de devoir faire appel à imagecoloralocate à chaque pixel
$couleurs = array();
for($i = 0; $i < $iterations_max; $i++)
    $couleur[$i] = imagecolorallocate($image, 0, 0, $i*255/$iterations_max);

$debut = microtime(true);
for($x = 0; $x < $image_x; $x++){
    for($y = 0; $y < $image_y; $y++){
        $c_r = $x/$zoom+$x1;
        $c_i = $y/$zoom+$y1;
        $z_r = 0;
        $z_i = 0;
        $i   = 0;

        do{
            $tmp = $z_r;
            $z_r = $z_r*$z_r - $z_i*$z_i + $c_r;
            $z_i = 2*$tmp*$z_i + $c_i;
            $i++;
        } while($z_r*$z_r + $z_i*$z_i < 4 AND $i < $iterations_max);

        if($i == $iterations_max)
            imagesetpixel($image, $x, $y, $noir);
        else
            imagesetpixel($image, $x, $y, $couleur[$i]);
    }
}

$temps = round(microtime(true) - $debut, 3);

imagestring($image, 3, 1, 1, $temps, $blanc);

header('Content-type: image/png');
imagepng($image);
?>