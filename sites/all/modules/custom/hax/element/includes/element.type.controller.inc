<?php

/**
 * @file
 * Element controller class.
 */

/**
 * The Controller for Element entities.
 */
class ElementTypeController extends EntityAPIControllerExportable {
  /**
   * Create a Element type.
   *
   * @param array $values
   *   An array containing the possible values.
   *
   * @return object
   *   A type object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our Element.
    $values += array(
      'id' => '',
    );
    $entity_type = parent::create($values);

    return $entity_type;
  }
}
