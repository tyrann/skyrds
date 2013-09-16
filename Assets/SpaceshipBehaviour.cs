using UnityEngine;
using System.Collections;

public class SpaceshipBehaviour : MonoBehaviour
{
	public float speed = 10f;
	public float distanceFromGround = 0f;
	public bool isFalling = false;
	public GameObject spaceshipPrefab;
	public float force;
	public float gravity = Physics.gravity.y;
	private BoxCollider boxCollider;
	private float stability = 1;
	private Vector3[] cornersPoint = new Vector3[5];
	private  int nbSuspensions = 5;
	private Transform[] corners = new Transform[5];
	private Vector3 boxDimension;
	private bool physicsSet = false;
	private float timeElapsed = 0;
	private bool playing = true;
	private bool won = false;
	private float thrustReversal = 100000f;
	private float thrustBalance = 20f;
	private float lateralThrust = 5000f;
	private float liftThrust = 10000f;
	
	
	
	// Use this for initialization
	void Start ()
	{
		transform.position = GameObject.FindGameObjectWithTag ("Respawn").transform.position;
		init_physics ();
	}
	
	void Respawn ()
	{		
		Instantiate (spaceshipPrefab, GameObject.FindGameObjectWithTag ("Respawn").transform.position, Quaternion.identity);
		Destroy (gameObject);
		timeElapsed = 0;
	}
	
	// Update is called once per frame
	void FixedUpdate ()
	{
		if (playing) {
			distanceFromGround = transform.position.y - GameObject.FindGameObjectWithTag ("Ground").transform.position.y;
			float forwardMovement = (Input.GetAxis ("Vertical") > 0) ? Input.GetAxis ("Vertical") * speed * Time.deltaTime : 0f;
			float horizontalMovement = Input.GetAxis ("Horizontal") * speed * Time.deltaTime;
			foreach (Transform child in transform) {
				//Test each suspension for bool hasLift

			}
			//use the test above to decide if thrust can be applied
			if (Input.GetButton ("Jump")) {
				rigidbody.AddForce (Vector3.up * liftThrust, ForceMode.Force);
			}
			
			rigidbody.AddForce (Vector3.forward * forwardMovement * thrustReversal);
			rigidbody.AddRelativeTorque (0, 0, -(Input.GetAxis ("Horizontal")) * thrustBalance);
			rigidbody.AddRelativeForce ((Input.GetAxis ("Horizontal")) * lateralThrust, 0, 0);
			
//			transform.Translate (Vector3.forward * forwardMovement + Vector3.right * horizontalMovement);
			if (transform.position.y <= -6) {
				playing = false;
				won = false;
			}
			timeElapsed += Time.deltaTime;
		}
	}

	void init_physics ()
	{

		//Creates a box around the hovering object
		
		boxCollider = spaceshipPrefab.GetComponent ("BoxCollider") as BoxCollider;

		boxDimension = new Vector3 (boxCollider.size.x * spaceshipPrefab.transform.localScale.x, boxCollider.size.y * spaceshipPrefab.transform.localScale.y, boxCollider.size.z * spaceshipPrefab.transform.localScale.z) * stability;
		cornersPoint [0] = new Vector3 (transform.position.x - boxDimension.x / 2, transform.position.y - boxDimension.y / 2, transform.position.z + boxDimension.z / 2);
		cornersPoint [1] = new Vector3 (boxDimension.x / 2 + transform.position.x, transform.position.y - boxDimension.y / 2, transform.position.z + boxDimension.z / 2);
		cornersPoint [2] = new Vector3 (boxDimension.x / 2 + transform.position.x, transform.position.y - boxDimension.y / 2, transform.position.z - boxDimension.z / 2);
		cornersPoint [3] = new Vector3 (transform.position.x - boxDimension.x / 2, transform.position.y - boxDimension.y / 2, transform.position.z - boxDimension.z / 2);
		cornersPoint [4] = transform.position;


		for (int i =0; i<=cornersPoint.Length-1; i++) {

			GameObject suspension = GameObject.CreatePrimitive (PrimitiveType.Sphere);

			suspension.name = "Suspension" + "(" + i + ")";
			
			suspension.transform.parent = spaceshipPrefab.transform;

			suspension.transform.localPosition = transform.InverseTransformPoint (cornersPoint [i]);

			corners [i] = suspension.transform;
			//Adds the suspension script
			suspension.AddComponent ("SuspensionRay");
			
			
			Destroy (suspension.GetComponent ("MeshRenderer"));
			Destroy (suspension.GetComponent ("Collider"));

		}

		cornersPoint = null;

		physicsSet = true;
		
	}
	
	void initTrailRenderer (GameObject suspension)
	{
//		TrailRenderer trail=suspension.AddComponent("TrailRenderer");
//		trail.castShadows=true;
//		trail.receiveShadows=true;
//		trail.material=
	}
	
	void OnTriggerEnter (Collider other)
	{
		if (other.CompareTag ("Finish")) {
			won = true;
			playing = false;
		}
	}
	
	void OnGUI ()
	{
		System.TimeSpan t = System.TimeSpan.FromSeconds (timeElapsed);

		string timeFormat = string.Format ("{0:D2}:{1:D2}:{2:D3}ms", 
    			t.Minutes, 
    			t.Seconds, 
    			t.Milliseconds);
		GUI.Label (new Rect (10, 10, 100, 90), timeFormat);
		
		if (!playing) {
			GUI.Label (new Rect (400, 100, 100, 90), (won) ? "Won" : "Lost");
			if (GUI.Button (new Rect (10, 10, 200, 20), "Play !")) {
				Respawn ();
			}
		}
	}
}
