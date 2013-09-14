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
	// Use this for initialization
	void Start ()
	{
	}
	
	void Respawn ()
	{
		Instantiate (spaceshipPrefab, GameObject.FindGameObjectWithTag ("Respawn").transform.position, Quaternion.identity);
		Destroy (gameObject);
	}
	
	// Update is called once per frame
	void Update ()
	{
		distanceFromGround = transform.position.y - GameObject.FindGameObjectWithTag ("Ground").transform.position.y;
		float forwardMovement = (Input.GetAxis ("Vertical") > 0) ? Input.GetAxis ("Vertical") * speed * Time.deltaTime : 0f;
		float horizontalMovement = Input.GetAxis ("Horizontal") * speed * Time.deltaTime;
		
		transform.Translate (Vector3.forward * forwardMovement + Vector3.right * horizontalMovement);
				
		if (Input.GetButtonDown ("Jump") && !isFalling) {
			transform.rigidbody.AddForce (new Vector3 (0, 200, 0), ForceMode.Acceleration);
		}
		if (transform.position.y <= -4) {
			Respawn ();
		}
		
		if (distanceFromGround < 1) {
			Debug.Log ("Distance from ground is " + distanceFromGround);
			transform.rigidbody.AddForce(new Vector3(0, (-gravity * rigidbody.mass)*(1/distanceFromGround), 0), ForceMode.Force);
		}
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
