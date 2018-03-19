///var container;

var camera, scene, renderer;

var mouseX = 0, mouseY = 0;

var windowHalfX = window.innerWidth / 2;
var windowHalfY = window.innerHeight / 2;

function pageStart(){
	camera = new THREE.PerspectiveCamera( 45, window.innerWidth / window.innerHeight,1, 2000 );
	camera.position.z = 30;
	camera.position.x = 0;
	camera.position.y = -140;
	camera.lookAt({
		x : 0,
		y : 0,
		z : 0
	});
	
	
	
	scene = new THREE.Scene();
	
	var ambient = new THREE.AmbientLight(0x101030);
	scene.add( ambient );

	var directionalLight = new THREE.DirectionalLight( 0xffeedd );
	directionalLight.position.set(0, 0, 1 ).normalize();
	scene.add( directionalLight );
	
	
	// texture

	var manager = new THREE.LoadingManager();
	manager.onProgress = function ( item, loaded, total ) {

		console.log( item, loaded, total );

	};

	var textureLoader = new THREE.TextureLoader( manager );
	var texture = textureLoader.load( "./textures/sphere_baked.png" );

	// model

	var onProgress = function ( xhr ) {
		if ( xhr.lengthComputable ) {
			var percentComplete = xhr.loaded / xhr.total * 100;
			console.log( Math.round(percentComplete, 2) + '% downloaded' );
		}
	};

	var onError = function ( xhr ) {
	};

	var loader = new THREE.OBJLoader( manager );
	loader.load( "./models/sphere1.obj"), function ( object ) {

		object.traverse( function ( child ) {

			if ( child instanceof THREE.Mesh ) {

				child.material.map = texture;

			}

		} );

		object.position.y = - 95;
		scene.add( object );

	}, 
	onProgress, onError );
	
	
		renderer = new THREE.WebGLRenderer();
		renderer.setPixelRatio( window.devicePixelRatio );
		renderer.setSize( window.innerWidth, window.innerHeight );
		
		
		var container = document.getElementById('container');
		
		container.appendChild( renderer.domElement );

		document.addEventListener( 'mousemove', onDocumentMouseMove, false );

		//

	//	window.addEventListener( 'resize', onWindowResize, false );






}



function onWindowResize() {

	windowHalfX = window.innerWidth / 2;
	windowHalfY = window.innerHeight / 2;

	camera.aspect = window.innerWidth / window.innerHeight;
	camera.updateProjectionMatrix();

	renderer.setSize( window.innerWidth, window.innerHeight );

}

function onDocumentMouseMove( event ) {

	mouseX = ( event.clientX - windowHalfX ) / 2;
	mouseY = ( event.clientY - windowHalfY ) / 2;

}

//

function animate() {

	requestAnimationFrame( animate );
	render();

}

function render() {

	camera.position.x += ( mouseX - camera.position.x ) * .05;
	camera.position.y += ( - mouseY - camera.position.y ) * .05;

	camera.lookAt( scene.position );

	renderer.render( scene, camera );

}