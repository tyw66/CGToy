var container;

var camera, scene, renderer;

var mouseX = 0, mouseY = 0;

var windowHalfX = window.innerWidth / 2;
var windowHalfY = window.innerHeight / 2;


init();
animate();

function mk_model(objName,textureName,x,y,z){
	// load texture
	var manager = new THREE.LoadingManager();
		manager.onProgress = function ( item, loaded, total ) {
		console.log( item, loaded, total );
	};
	var textureLoader = new THREE.TextureLoader( manager );
	var mytexture = textureLoader.load( textureName );

	//set shader
	var vShader = 'void main(){gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);}';
	
	var fShader = 'void main(){gl_FragColor = vec4(0.0, 0.8, 1.0, 1.0);}';
	var shaderMaterial =
	  new THREE.ShaderMaterial({
		uniforms:{
			tex: {type:"t",value: mytexture},
		},
		attributes:{
			
		},
		vertexShader:   vShader,
		fragmentShader: fShader
	  }); 
	
	
	
	// load model
	var loader = new THREE.OBJLoader( manager );
	var object;
	loader.load( objName, afterLoad, onProgress, onError );
	
	
	var onProgress = function ( xhr ) {
		if ( xhr.lengthComputable ) {
			var percentComplete = xhr.loaded / xhr.total * 100;
			console.log( Math.round(percentComplete, 2) + '% downloaded' );
		}
	};
	var onError = function ( xhr ) {
	};


	function afterLoad( object ) {
		object.traverse( function ( child ) {
			if ( child instanceof THREE.Mesh ) {
				shaderMaterial.map = texture;
				child.material = shaderMaterial;
				//child.material.map = texture;
			}
		} );
		//设置模型在场景中的位置
		object.position.x = x;
		object.position.y = y;
		object.position.z = z;	
		scene.add(object);
	}
	

}

function init() {	
	// setup scene
	scene = new THREE.Scene();

	// setup light
	var ambientLight = new THREE.AmbientLight( 0xFFFFFF, 1.0 );//颜色 强度
	scene.add( ambientLight );
	
	// setup camera
	camera = new THREE.PerspectiveCamera( 30, window.innerWidth / window.innerHeight, 1, 2000 );
	camera.position.x = 0;
	camera.position.y = 0;
	camera.position.z = 250;	
	scene.add( camera );

	// load model
	mk_model('models/sphere.obj','texture/sphere_baked.png',0,-30,0);
	
	//setup renderer
	renderer = new THREE.WebGLRenderer();
	renderer.setPixelRatio( window.devicePixelRatio );
	renderer.setSize( window.innerWidth, window.innerHeight );	
	renderer.setClearColor(0xEEEEEE, 1.0);
		
	//layout	
	container = document.createElement( 'div' );
	container.appendChild( renderer.domElement );
	document.body.appendChild( container );	
	document.addEventListener( 'mousemove', onDocumentMouseMove, false );
	window.addEventListener( 'resize', onWindowResize, false );

}

function onWindowResize() {
	windowHalfX = window.innerWidth / 2;
	windowHalfY = window.innerHeight / 2;
	camera.aspect = window.innerWidth / window.innerHeight;
	camera.updateProjectionMatrix();
	renderer.setSize( window.innerWidth, window.innerHeight );
}

function onDocumentMouseMove( event ) {
	mouseX = ( event.clientX - windowHalfX ) ;
	mouseY = ( event.clientY - windowHalfY ) ;
}

function animate() {
	requestAnimationFrame( animate );
	render();
}

function render() {
	camera.position.x += ( mouseX - camera.position.x );
	camera.position.y += ( - mouseY - camera.position.y ) ;
	camera.lookAt( scene.position );
	renderer.render( scene, camera );
}



