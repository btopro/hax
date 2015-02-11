<?php

/**
 * @file
 * Hax Gridplate controller class.
 */

/**
 * The Controller for Hax Gridplate entities.
 */
class HaxGridplateTypeController extends EntityAPIControllerExportable {
  /**
   * Create a Hax Gridplate type.
   *
   * @param array $values
   *   An array containing the possible values.
   *
   * @return object
   *   A type object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our Hax Gridplate.
    $values += array(
      'id' => '',
    );
    $entity_type = parent::create($values);

    return $entity_type;
  }
}
