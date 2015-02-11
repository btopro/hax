<?php

/**
 * @file
 * Hax Gridplate controller class.
 */

/**
 * The Controller for Hax Gridplate entities.
 */
class HaxGridplateController extends EntityAPIController {
  /**
   * Create a Hax Gridplate.
   *
   * @param array $values
   *   An array containing the possible values.
   *
   * @return object
   *   A object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our entity.
    $values += array(
      'hax_gridplate_id' => '',
      'is_new' => TRUE,
      'label' => '',
    );

    $entity = parent::create($values);

    return $entity;
  }
}
