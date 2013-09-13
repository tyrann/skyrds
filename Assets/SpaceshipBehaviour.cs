using UnityEngine;
using System.Collections;

public class SpaceshipBehaviour : MonoBehaviour {
	public float speed = 10f;
	private bool isFalling = false;
	public GameObject spaceshipPrefab;
	// Use this for initialization
	void Start () {

	}
	
	void Respawn() {
		Instantiate(spaceshipPrefab, GameObject.FindGameObjectWithTag("Respawn").transform.position, Quaternion.identity);
		Destroy(gameObject);
	}
	
	// Update is called once per frame
	void Update () {
     	float forwardMovement = (Input.GetAxis("Vertical") > 0) ? Input.GetAxis("Vertical") * speed * Time.deltaTime : 0f;
     	float horizontalMovement = Input.GetAxis("Horizontal") * speed * Time.deltaTime;
		
        transform.Translate(Vector3.forward * forwardMovement + Vector3.right * horizontalMovement);
				
		if (Input.GetButtonDown("Jump") && !isFalling) {
			transform.rigidbody.AddForce(new Vector3(0, 200, 0), ForceMode.Acceleration);
		}
		if (transform.position.y <= -4) {
			Respawn();
		}
	}
	
	void OnCollisionEnter(Collision other) {
		Debug.Log("enter");
		if (other.collider.CompareTag("Ground")) {
			Debug.Log("enter ground");
		 isFalling = false;
		}
	}
	
	void OnCollisionExit(Collision other) {
		if (other.collider.CompareTag("Ground")) {
		 isFalling = true;
		}
	}
	
	void OnTriggerEnter(Collider other) {
		if (other.CompareTag("Finish")) {
			Respawn();
		}
	}
}
