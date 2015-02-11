<?php

/**
 * @file
 * Hax Element controller class.
 */

/**
 * The Controller for Hax Element entities.
 */
class HaxElementTypeController extends EntityAPIControllerExportable {
  /**
   * Create a Hax Element type.
   *
   * @param array $values
   *   An array containing the possible values.
   *
   * @return object
   *   A type object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our Hax Element.
    $values += array(
      'id' => '',
    );
    $entity_type = parent::create($values);

    return $entity_type;
  }
}
