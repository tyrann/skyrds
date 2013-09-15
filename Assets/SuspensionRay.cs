using UnityEngine;
using System.Collections;

public class SuspensionRay : MonoBehaviour
{
	float suspensionRange = 0.7f;
	float suspensionForce = 300f;
	float suspensionDamp = 15.00f;
	private RaycastHit hit;
	private Rigidbody parent;
	GameObject levelParent;


	void FixedUpdate ()
	{	
		
		parent = transform.root.rigidbody;
		Vector3 down = transform.TransformDirection (Vector3.down);
		Vector3 worldDown = levelParent.transform.TransformDirection (Vector3.down);
		if (Physics.Raycast (transform.position, worldDown, out hit, suspensionRange) && hit.collider.transform.root != transform.root) {
			Vector3 velocityAtTouch = parent.GetPointVelocity (hit.point);
			float compression = hit.distance / (suspensionRange);
			compression = -compression + 1;
			Vector3 counterForce = (-worldDown * compression * suspensionForce);
			Vector3 t = transform.InverseTransformDirection (velocityAtTouch);
			t.z = t.x = 0;
			Vector3 shockDrag = levelParent.transform.TransformDirection (t) * -suspensionDamp;
			parent.AddForceAtPosition (counterForce + shockDrag, hit.point);
		}
	}

	// Use this for initialization
	void Start ()
	{
		levelParent = GameObject.FindGameObjectWithTag ("Player");
		parent = transform.root.rigidbody;
	}

	// Show yellow Rays
	void OnDrawGizmos ()
	{
		Gizmos.color = Color.yellow;
		Gizmos.DrawRay (transform.position, levelParent.transform.TransformDirection (Vector3.up) * -suspensionRange);
		Gizmos.color=Color.white;
		Gizmos.DrawWireSphere(transform.position,0.4f);
	}
}