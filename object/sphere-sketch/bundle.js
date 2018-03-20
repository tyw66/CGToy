///var container;

var camera, scene, renderer;

var mouseX = 0, mouseY = 0;

var windowHalfX = window.innerWidth / 2;
var windowHalfY = window.innerHeight / 2;

function pageStart(){
	//建立摄像机
	camera = new THREE.PerspectiveCamera( 45, window.innerWidth / window.innerHeight,1, 2000 );
	camera.position.z = 30;
	camera.position.x = 0;
	camera.position.y = -140;
	camera.lookAt({
		x : 0,
		y : 0,
		z : 0
	});
	
	//建立场景	
	scene = new THREE.Scene();	
	var ambient = new THREE.AmbientLight(0x101030);
	scene.add( ambient );
	
	//建立灯光
	var directionalLight = new THREE.DirectionalLight( 0xffeedd );
	directionalLight.position.set(0, 0, 1 ).normalize();
	                
	var light = new THREE.DirectionalLight(0xFF0000, 1.0, 0);
    light.position.set(100, 100, 200);
	
	scene.add( light );
	
	
	
	//导入贴图
	var manager = new THREE.LoadingManager();
	manager.onProgress = function ( item, loaded, total ) {
		console.log( item, loaded, total );
	};
	var textureLoader = new THREE.TextureLoader( manager );
	var texture = textureLoader.load( "textures/test/male.jpg" );

	//导入模型
	var onProgress = function ( xhr ) {
		if ( xhr.lengthComputable ) {
			var percentComplete = xhr.loaded / xhr.total * 100;
			console.log( Math.round(percentComplete, 2) + '% downloaded' );
		}
	};
	
	var onError = function ( xhr ) {
	};

	var loader = new THREE.OBJLoader( manager );
	loader.load('models/test/male.obj', function ( object ) {
		object.traverse( function ( child ) {
			if ( child instanceof THREE.Mesh ) {
				child.material.map = texture;
			}
		} );

		object.position.x = 0;
		object.position.y = 0;
		object.position.z = 0;
		
		scene.add( object );

	}, onProgress, onError );
	
	
	
	//建立渲染器
	renderer = new THREE.WebGLRenderer();
	//renderer.setPixelRatio( window.devicePixelRatio );
	renderer.setSize( window.innerWidth, window.innerHeight );
	renderer.setClearColor(0xCCCCCC, 1.0);

	
	var container = document.getElementById('container');	
	container.appendChild( renderer.domElement );
	

	renderer.render( scene, camera );


}

function animate() {

	requestAnimationFrame( animate );
	renderer.render( scene, camera );

}

