using UnityEngine;
using System.Collections;

public class SpaceshipBehaviour : MonoBehaviour
{
	public float speed = 10f;
	public float distanceFromGround = 0f;
	private bool isFalling = false;
	public GameObject spaceshipPrefab;
	public float force;
	public float gravity = Physics.gravity.y;
	private BoxCollider boxCollider;
	private float stability = 1;
	private Vector3[] cornersPoint = new Vector3[5];
	private  int nbSuspensions= 5;
	private Transform[] corners = new Transform[5];
	private Vector3 boxDimension;
	private bool physicsSet = false;
	
	
	// Use this for initialization
	void Start ()
	{
		init_physics ();		
	}
	
	void Respawn ()
	{
		Instantiate (spaceshipPrefab, GameObject.FindGameObjectWithTag ("Respawn").transform.position, Quaternion.identity);
		for (int i =0; i<=nbSuspensions-1; i++) {	
			//DESTROY THE CHILD SUSPENSION

		}
		Destroy (gameObject);
	}
	
	// Update is called once per frame
	void FixedUpdate ()
	{
		distanceFromGround = transform.position.y - GameObject.FindGameObjectWithTag ("Ground").transform.position.y;
		float forwardMovement = (Input.GetAxis ("Vertical") > 0) ? Input.GetAxis ("Vertical") * speed * Time.deltaTime : 0f;
		float horizontalMovement = Input.GetAxis ("Horizontal") * speed * Time.deltaTime;
		
		transform.Translate (Vector3.forward * forwardMovement + Vector3.right * horizontalMovement);
//				
//		if (Input.GetButtonDown ("Jump") && !isFalling) {
//			transform.rigidbody.AddForce (new Vector3 (0, 200, 0), ForceMode.Acceleration);
//		}
//		if (transform.position.y <= -4) {
//			Respawn ();
//		}
//		
//		if (distanceFromGround < 1) {
//			Debug.Log ("Distance from ground is " + distanceFromGround);
//			transform.rigidbody.AddForce(new Vector3(0, (-gravity * rigidbody.mass)*(1/distanceFromGround), 0), ForceMode.Force);
//		}
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

			Destroy (suspension.GetComponent ("MeshRenderer"));
			Destroy (suspension.GetComponent ("Collider"));

		}

		cornersPoint = null;

		physicsSet = true;
		
	}
	
//	void OnCollisionEnter(Collision other) {
//		if (other.collider.CompareTag("Ground")) {
//		 isFalling = false;
//		}
//	}
//	
//	void OnCollisionExit(Collision other) {
//		if (other.collider.CompareTag("Ground")) {
//		 isFalling = true;
//		}
//	}
	
	void OnTriggerEnter (Collider other)
	{
		if (other.CompareTag ("Finish")) {
			Respawn ();
		}
	}
}
